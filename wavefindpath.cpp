extern "C" {
#include "sc_memory_headers.h"
#include "sc_helper.h"
}

#include "wavefindpath.h"
#include <stdio.h>
#include <unistd.h>
#include "model/Node.h"
#include <vector>

using namespace std;

sc_memory_context *context;

sc_addr graph, rrel_arcs, rrel_nodes;
FILE *f;

vector<Node> nodeVector;
int uniqId;

sc_char *printContent(sc_memory_context *context, sc_addr element)
{
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data;
    if (sc_memory_get_link_content(context, element, &stream) != SC_RESULT_OK)
    {
        printf("Content reading error\n");
    }
    sc_stream_get_length(stream, &length);
    data = (sc_char *)calloc(length + 1, sizeof(sc_char));
    sc_stream_read_data(stream, data, length, &read_length);
    data[length] = '\0';
    sc_stream_free(stream);
    return data;
}

void run_test()
{
    //char gr[12] = "rootElement";
    char gr[24] = "concertedKB_hash_iF95K2";
    sc_helper_resolve_system_identifier(context, gr, &graph);

    sc_iterator3 *it = sc_iterator3_f_a_a_new(context,
                                              graph,
                                              sc_type_arc_pos_const_perm,
                                              0);
    std::string x = "";
    while (SC_TRUE == sc_iterator3_next(it)) {
        sc_addr t_arc = sc_iterator3_value(it, 2);
        if (printEl(context, t_arc, f)) {
            fprintf(f, ";;\n");
        }
    }
    //std::string x = "";
    fprintf(f, "\n");
    for (int i = 0; i < nodeVector.size(); i++) {
        if (printEl2(context, nodeVector.at(i).getAddr(), f)) {
            for (int j = 0; j < nodeVector.at(i).getTypes().size(); j++) {
                fprintf(f, "<-%s;", nodeVector.at(i).getTypes().at(j).c_str());
            }
      //      x.append(";\n");
            fprintf(f, ";\n");
        }
    }

    sc_iterator3_free(it);
    nodeVector.clear();
}

bool printEl2(sc_memory_context *context, sc_addr element, FILE *f) {
    bool isPrinted = false;
    sc_addr idtf;
    sc_type type;
    sc_memory_get_element_type(context, element, &type);
    if (((sc_type_node & type) == sc_type_node) |
        ((sc_type_node_struct & type) == sc_type_node_struct)) {
        try {
            if (SC_RESULT_OK == sc_helper_get_system_identifier_link(context, element, &idtf)) {
                sc_stream *stream;
                sc_uint32 length = 0, read_length = 0;
                sc_char *data;
                sc_memory_get_link_content(context, idtf, &stream);
                sc_stream_get_length(stream, &length);
                data = (sc_char *) calloc(length + 1, sizeof(sc_char));
                sc_stream_read_data(stream, data, length, &read_length);
                data[length] = '\0';
                fprintf(f, "%s", data);
                sc_stream_free(stream);
                free(data);
            } else {
                fprintf(f, "..%d", getIdByAddr(element));
            }
        }
        catch (...) {
            fprintf(f, "%s", "fail");
        }
        isPrinted = true;
    }
    return isPrinted;
}

void printEdge(sc_addr element, const char *connector, Node *node) {
    sc_addr elem1, elem2;
    sc_memory_get_arc_begin(context, element, &elem1);
    sc_memory_get_arc_end(context, element, &elem2);
    fprintf(f, "(");
    if (!printEl(context, elem1, f)) {
        int x = getIdByAddr(elem1);
        if (x!=0) {
            fprintf(f, "..%d", x);
        }
        else {
            printEl2(context, elem1, f);
        }
    }
    fprintf(f, " %s ", connector);
    if (!printEl(context, elem2,f)) {
        int x = getIdByAddr(elem2);
        if (x!=0) {
            fprintf(f, "..%d", x);
        }
        else {
            printEl2(context, elem2, f);
        }
    }
    fprintf(f, ")");
    node = new Node(element, uniqId);
    nodeVector.push_back(*node);
    uniqId++;
}

bool printEl(sc_memory_context *context, sc_addr element, FILE *f)
{
    bool answer = false;
    if (isAddrExist(element)) {
        return answer;
    }
    sc_addr idtf;
    sc_type type;
    Node *node = NULL;
    sc_memory_get_element_type(context, element, &type);
    if (((sc_type_node & type) == sc_type_node) |
        ((sc_type_node_struct & type) == sc_type_node_struct)) {
        try {
            if (SC_RESULT_OK == sc_helper_get_system_identifier_link(context, element, &idtf))
            {
                sc_stream *stream;
                sc_uint32 length = 0, read_length = 0;
                sc_char *data;
                sc_memory_get_link_content(context, idtf, &stream);
                sc_stream_get_length(stream, &length);
                data = (sc_char *)calloc(length + 1, sizeof(sc_char));
                sc_stream_read_data(stream, data, length, &read_length);
                data[length] = '\0';
                fprintf(f, "%s", data);
                node = new Node(element, 0);
                nodeVector.push_back(*node);
                answer = true;
                sc_stream_free(stream);
                free(data);
            }
            else
            {
                node = new Node(element, uniqId);
                nodeVector.push_back(*node);
                fprintf(f, "..%d", uniqId);
                uniqId++;
                answer = true;
            }
        }
        catch (...) {
            fprintf(f, "%s", "fail");
        }
    }
    if ((sc_type_link & type) == sc_type_link) {
        fprintf(f, "[%s]", printContent(context, element));
        node = new Node(element, uniqId);
        nodeVector.push_back(*node);
        uniqId++;
        answer = true;
        //return;
    }
    if ((sc_type_arc_common & type) == sc_type_arc_common) {
        const char* connector = ">";
        if ((sc_type_var & type) == sc_type_var) {
            connector = "_=>";
        }
        if ((sc_type_const & type) == sc_type_const) {
            connector = "=>";
        }
        printEdge(element, connector, node);
        answer = true;
        return answer;
    }
    if ((sc_type_arc_pos_const_perm & type) == sc_type_arc_pos_const_perm) {
        const char* connector = "->";
        printEdge(element, connector, node);
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
        printEdge(element, connector, node);
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
        printEdge(element, connector, node);
        answer = true;
        return answer;
    }
    if ((sc_type_const & type) == sc_type_const) {
        if (node!= NULL) {
            nodeVector.at(nodeVector.size()-1).addType("sc_type_const");
        }
    }
    if ((sc_type_var & type) == sc_type_var) {
        if (node!= NULL) {
            nodeVector.at(nodeVector.size()-1).addType("sc_type_var");
        }
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

    uniqId = 1;
    f = fopen("/home/alexander/Desktop/KnowledgeDump.txt", "w");
    run_test();
    fclose(f);
    sc_memory_context_free(context);
    sc_memory_shutdown(SC_TRUE);

    return 0;
}
