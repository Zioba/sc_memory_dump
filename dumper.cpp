extern "C" {
#include "sc_memory_headers.h"
#include "sc_helper.h"
}

#include "dumper.h"
#include <cstdio>
#include <unistd.h>
#include "model/Node.h"
#include <vector>

using namespace std;

sc_memory_context *context;

sc_addr graph;

vector<Node> nodeVector;
int uniqId;

sc_char *printContent(sc_addr element)
{
    sc_uint32 read_length;
    sc_char *data = getScLinkData(element, read_length);
    string format;
    if (checkLinkFormat(element, &format)) {
        return saveContentFile(element, data, format, read_length);
    }
    return data;
}

bool checkLinkFormat(sc_addr element, string *format) {
    bool result = false;
    sc_addr nrel_format;
    sc_uint32 read_length;
    sc_helper_resolve_system_identifier(context, NREL_FORMAT_STR, &nrel_format);
    sc_iterator5 *it = sc_iterator5_f_a_a_a_f_new(context,
                                              element,
                                              sc_type_arc_common | sc_type_const,
                                              0,
                                              sc_type_arc_pos_const_perm,
                                              nrel_format);
    if (SC_TRUE == sc_iterator5_next(it)) {
        sc_addr t_node = sc_iterator5_value(it, 2);
        sc_addr idtf;
        if (SC_RESULT_OK == sc_helper_get_system_identifier_link(context, t_node, &idtf))
        {
            sc_char *temp = getScLinkData(idtf, read_length);
            string temp_string = "";
            temp_string.append(temp);
            size_t n = temp_string.find_last_of('_');
            if (n != string::npos)
                *format = temp_string.substr(n + 1);
            result=true;
        }
    }
    sc_iterator5_free(it);
    return result;
}

sc_char *saveContentFile(sc_addr element, char* data, string format, sc_uint32 &read_length) {
    string filename = "content_";
    string answer = "file://content/";
    filename.append(to_string(element.seg));
    filename.append(to_string(element.offset));
    filename.append(".");
    filename.append(format);
    FILE *f;
    f = fopen((DUMP_CONTENT_FOLDER + filename).c_str(), "w");
    for (int i = 0; i < read_length; i++) {
        fprintf(f, "%c", data[i]);
    }
    fclose(f);
    answer.append(filename);
    char *cstr = new char[answer.length() + 1];
    strcpy(cstr, answer.c_str());
    return cstr;
}

void run_test()
{
    FILE *f;
    f = fopen("/home/alexander/Desktop/KnowledgeDump.scs", "w");
    //char gr[12] = "rootElement";
    char gr[24] = "concertedKB_hash_iF95K2";
    sc_helper_resolve_system_identifier(context, gr, &graph);

    sc_iterator3 *it = sc_iterator3_f_a_a_new(context,
                                              graph,
                                              sc_type_arc_pos_const_perm,
                                              0);
    string *x = new std::string("");
    while (SC_TRUE == sc_iterator3_next(it)) {
        sc_addr t_arc = sc_iterator3_value(it, 2);
        x->clear();
        if (printEl(t_arc, x)) {
            string x2 = x->substr(1, x->size()-2);
            x2.append(";;\n");
            size_t found = x2.find("nrel_system_identifier");
            if (found == std::string::npos) {
                fprintf(f, "%s", x2.c_str());
            }
        }
    }
    fprintf(f, "\n");
    for (int i = 0; i < nodeVector.size(); i++) {
        x->clear();
        if (printEl2(nodeVector.at(i).getAddr(), x)) {
            if (!nodeVector.at(i).getTypes().empty()) {
                fprintf(f, "%s", x->c_str());
            }
            for (int j = 0; j < nodeVector.at(i).getTypes().size(); j++) {
                fprintf(f, "<-%s;", nodeVector.at(i).getTypes().at(j).c_str());
            }
            if (!nodeVector.at(i).getTypes().empty()) {
                fprintf(f, ";\n");
            }
        }
    }

    sc_iterator3_free(it);
    nodeVector.clear();
    fclose(f);
}

bool printEl2(sc_addr element, string *strBuilder) {
    bool isPrinted = false;
    sc_addr idtf;
    sc_type type;
    sc_uint32 read_length;
    sc_memory_get_element_type(context, element, &type);
    if (((sc_type_node & type) == sc_type_node) |
        ((sc_type_node_struct & type) == sc_type_node_struct)) {
        try {
            if (SC_RESULT_OK == sc_helper_get_system_identifier_link(context, element, &idtf)) {
                sc_char *data = getScLinkData(idtf, read_length);
                strBuilder->append(data);
                free(data);
            } else {
                strBuilder->append("..").append(to_string(getIdByAddr(element)));
            }
        }
        catch (...) {
            strBuilder->append("fail");
        }
        isPrinted = true;
    }
    return isPrinted;
}

void printEdge(sc_addr element, const char *connector, Node *node, string *strBuilder) {
    sc_addr elem1, elem2;
    sc_memory_get_arc_begin(context, element, &elem1);
    sc_memory_get_arc_end(context, element, &elem2);
    strBuilder->append("(");
    if (!printEl(elem1, strBuilder)) {
        int x = getIdByAddr(elem1);
        if (x!=0) {
            strBuilder->append("..").append(to_string(x));
        }
        else {
            printEl2(elem1, strBuilder);
        }
    }
    strBuilder->append(connector);
    if (!printEl(elem2, strBuilder)) {
        int x = getIdByAddr(elem2);
        if (x!=0) {
            strBuilder->append("..").append(to_string(x));
        }
        else {
            printEl2(elem2, strBuilder);
        }
    }
    strBuilder->append(")");
    node = new Node(element, uniqId);
    nodeVector.push_back(*node);
    uniqId++;
}

bool printEl(sc_addr element, string* strBuilder)
{
    bool answer = false;
    if (isAddrExist(element)) {
        return answer;
    }
    sc_addr idtf;
    sc_type type;
    sc_uint32 read_length;
    Node *node = NULL;
    sc_memory_get_element_type(context, element, &type);
    if (((sc_type_node & type) == sc_type_node) |
        ((sc_type_node_struct & type) == sc_type_node_struct)) {
        try {
            if (SC_RESULT_OK == sc_helper_get_system_identifier_link(context, element, &idtf))
            {
                sc_char *data = getScLinkData(idtf, read_length);
                strBuilder->append(data);
                node = new Node(element, 0);
                nodeVector.push_back(*node);
                answer = true;
                free(data);
            }
            else
            {
                node = new Node(element, uniqId);
                nodeVector.push_back(*node);
                strBuilder->append("..").append(to_string(uniqId));
                uniqId++;
                answer = true;
            }
        }
        catch (...) {
            strBuilder->append("fail");
        }
    }
    if ((sc_type_link & type) == sc_type_link) {
        strBuilder->append("[").append(printContent(element)).append("]");
        node = new Node(element, uniqId);
        nodeVector.push_back(*node);
        uniqId++;
        answer = true;
    }
    if ((sc_type_arc_common & type) == sc_type_arc_common) {
        const char* connector = ">";
        if ((sc_type_var & type) == sc_type_var) {
            connector = "_=>";
        }
        if ((sc_type_const & type) == sc_type_const) {
            connector = "=>";
        }
        printEdge(element, connector, node, strBuilder);
        answer = true;
        return answer;
    }
    if ((sc_type_arc_pos_const_perm & type) == sc_type_arc_pos_const_perm) {
        const char* connector = "->";
        printEdge(element, connector, node, strBuilder);
        answer = true;
        return answer;
    }
    if ((sc_type_edge_common & type) == sc_type_edge_common) {
        const char* connector = "<>";
        if ((sc_type_const & type) == sc_type_const) {
            connector = "<=>";
        }
        if ((sc_type_var & type) == sc_type_var) {
            connector = "_<=>";
        }
        printEdge(element, connector, node, strBuilder);
        answer = true;
        return answer;
    }
    if ((sc_type_arc_access & type) == sc_type_arc_access) {
        const char* connector = "..>";
        if (((sc_type_arc_pos & type) == sc_type_arc_pos) &&
            ((sc_type_var & type) == sc_type_var) &&
            ((sc_type_arc_perm & type) == sc_type_arc_perm)) {
            connector = "_->";
        }
        if (((sc_type_arc_neg & type) == sc_type_arc_neg) &&
            ((sc_type_const & type) == sc_type_const) &&
            ((sc_type_arc_perm & type) == sc_type_arc_perm)) {
            connector = "-|>";
        }
        if (((sc_type_arc_neg & type) == sc_type_arc_neg) &&
            ((sc_type_var & type) == sc_type_var) &&
            ((sc_type_arc_perm & type) == sc_type_arc_perm)) {
            connector = "_-|>";
        }
        if (((sc_type_arc_fuz & type) == sc_type_arc_fuz) &&
            ((sc_type_const & type) == sc_type_const) &&
            ((sc_type_arc_perm & type) == sc_type_arc_perm)) {
            connector = "-/>";
        }
        if (((sc_type_arc_fuz & type) == sc_type_arc_fuz) &&
            ((sc_type_var & type) == sc_type_var) &&
            ((sc_type_arc_perm & type) == sc_type_arc_perm)) {
            connector = "_-/>";
        }
        if (((sc_type_arc_pos & type) == sc_type_arc_pos) &&
            ((sc_type_const & type) == sc_type_const) &&
            ((sc_type_arc_temp & type) == sc_type_arc_temp)) {
            connector = "~>";
        }
        if (((sc_type_arc_pos & type) == sc_type_arc_pos) &&
            ((sc_type_var & type) == sc_type_var) &&
            ((sc_type_arc_temp & type) == sc_type_arc_temp)) {
            connector = "_~>";
        }
        if (((sc_type_arc_neg & type) == sc_type_arc_neg) &&
            ((sc_type_const & type) == sc_type_const) &&
            ((sc_type_arc_temp & type) == sc_type_arc_temp)) {
            connector = "~|>";
        }
        if (((sc_type_arc_neg & type) == sc_type_arc_neg) &&
            ((sc_type_var & type) == sc_type_var) &&
            ((sc_type_arc_temp & type) == sc_type_arc_temp)) {
            connector = "_~|>";
        }
        if (((sc_type_arc_fuz & type) == sc_type_arc_fuz) &&
            ((sc_type_const & type) == sc_type_const) &&
            ((sc_type_arc_temp & type) == sc_type_arc_temp)) {
            connector = "~/>";
        }
        if (((sc_type_arc_fuz & type) == sc_type_arc_fuz) &&
            ((sc_type_var & type) == sc_type_var) &&
            ((sc_type_arc_temp & type) == sc_type_arc_temp)) {
            connector = "_~/>";
        }
        printEdge(element, connector, node, strBuilder);
        answer = true;
        return answer;
    }
    if ((sc_type_node_tuple & type) == sc_type_node_tuple) {
        if (node!= NULL) {
            nodeVector.at(nodeVector.size()-1).addType("sc_type_node_tuple");
        }
    }
    if ((sc_type_node_role & type) == sc_type_node_role) {
        if (node!= NULL) {
            nodeVector.at(nodeVector.size()-1).addType("sc_type_node_role");
        }
    }
    if ((sc_type_node_norole & type) == sc_type_node_norole) {
        if (node!= NULL) {
            nodeVector.at(nodeVector.size()-1).addType("sc_type_node_norole");
        }
    }
    if ((sc_type_node_class & type) == sc_type_node_class) {
        if (node!= NULL) {
            nodeVector.at(nodeVector.size()-1).addType("sc_type_node_class");
        }
    }
    if ((sc_type_node_abstract & type) == sc_type_node_abstract) {
        if (node!= NULL) {
            nodeVector.at(nodeVector.size()-1).addType("sc_type_node_abstract");
        }
    }
    if ((sc_type_node_material & type) == sc_type_node_material) {
        if (node!= NULL) {
            nodeVector.at(nodeVector.size()-1).addType("sc_type_node_material");
        }
    }
    return answer;
}

sc_char *getScLinkData(const sc_addr &idtf, sc_uint32 &read_length) {
    sc_stream *stream;
    sc_uint32 length;
    if (sc_memory_get_link_content(context, idtf, &stream) != SC_RESULT_OK)
    {
        printf("Content reading error\n");
    }
    sc_stream_get_length(stream, &length);
    auto data = (sc_char *)calloc(length + 1, sizeof(sc_char));
    sc_stream_read_data(stream, data, length, &read_length);
    data[length] = '\0';
    sc_stream_free(stream);
    return data;
}

bool isAddrExist(sc_addr addr) {
    bool answer = false;
    for (int i = 0; i < nodeVector.size(); i++) {
        if (addr.offset == nodeVector.at(i).getAddr().offset && addr.seg == nodeVector.at(i).getAddr().seg) {
            answer = true;
            return answer;
        }
    }
    return answer;
}

int getIdByAddr(sc_addr addr) {
    for (int i = 0; i < nodeVector.size(); i++) {
        if (addr.offset == nodeVector.at(i).getAddr().offset && addr.seg == nodeVector.at(i).getAddr().seg) {
            return nodeVector.at(i).getId();
        }
    }
    return -1;
}

void testPictureSaveFunction() {
    sc_addr testAddr = sc_memory_node_new(context, sc_type_link);
    string file = "/home/alexander/Desktop/content/explanation_for_nrel_implication.png";
    string file2 = "/home/alexander/Desktop/content/explanation_for_nrel_implication_new.png";
    //f = fopen(file.c_str(), "w");
    sc_stream *stream = sc_stream_file_new(file.c_str(), SC_STREAM_FLAG_READ);
    sc_char* data;
    sc_uint32 read_length = 0;
    if (stream)
    {
        sc_memory_set_link_content(context, testAddr, stream);
        data = getScLinkData(testAddr, read_length);
        sc_stream_free(stream);
    }
    FILE *f;
    f = fopen(file2.c_str(), "w");
    for (int i =0; i < read_length; i++) {
        fprintf(f, "%c", data[i]);
    }
    fclose(f);
}

int main()
{
    sc_memory_params params;
    sc_memory_params_clear(&params);
    params.repo_path = "/home/alexander/work/ostis/kb.bin";
    params.config_file = "/home/alexander/work/ostis/config/sc-web.ini";
    params.ext_path = "/home/alexander/work/ostis/sc-machine/bin/extensions";
    params.clear = SC_FALSE;
    sc_memory_initialize(&params);
    context = sc_memory_context_new(sc_access_lvl_make_max);

    //testPictureSaveFunction();

    uniqId = 1;
    run_test();
    sc_memory_context_free(context);
    sc_memory_shutdown(SC_TRUE);

    return 0;
}
