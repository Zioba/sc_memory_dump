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
{;

    char gr[12] = "rootElement";
    //char gr[] = "graph";
    sc_helper_resolve_system_identifier(context, gr, &graph);

    printEl(context, graph, f);
    fprintf(f, "%d %d \n", graph.seg, graph.offset);
    fprintf(f, "\n----------------------\n");

    sc_iterator3 *it = sc_iterator3_f_a_a_new(context,
                                              graph,
                                              sc_type_arc_pos_const_perm,
                                              0);

    while (SC_TRUE == sc_iterator3_next(it)) {
        sc_addr t_arc = sc_iterator3_value(it, 2);
        if (printEl(context, t_arc, f)) {
            fprintf(f, "\n");
        }
    }

    sc_iterator3_free(it);
}

void printEl2(sc_memory_context *context, sc_addr element, FILE *f) {
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
                fprintf(f, "%u|%u", element.seg, element.offset);
            }
        }
        catch (...) {
            fprintf(f, "%s", "fail");
        }
    }
}

bool printEl(sc_memory_context *context, sc_addr element, FILE *f)
{
    bool answer = false;
    if (isAddrExist(element)) {
        return answer;
    }
    sc_addr idtf;
    sc_type type;
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
                Node *node = new Node(element, 0);
                nodeVector.push_back(*node);
                answer = true;
                sc_stream_free(stream);
                free(data);
            }
            else
            {
                fprintf(f, "%u|%u", element.seg, element.offset);
                Node *node = new Node(element, uniqId);
                nodeVector.push_back(*node);
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
        Node *node = new Node(element, uniqId);
        nodeVector.push_back(*node);
        uniqId++;
        answer = true;
        //return;
    }
    if ((sc_type_arc_common & type) == sc_type_arc_common) {
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
        fprintf(f, " => ");
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
        answer = true;
        Node *node = new Node(element, uniqId);
        nodeVector.push_back(*node);
        uniqId++;
        //return;
    }
    if ((sc_type_arc_pos_const_perm & type) == sc_type_arc_pos_const_perm) {
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
        fprintf(f, " -> ");
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
        answer = true;
        Node *node = new Node(element, uniqId);
        nodeVector.push_back(*node);
        uniqId++;
        //return;
    }
//    fprintf(f, " unknowElement");
//    if ((sc_type_edge_common & type) == sc_type_edge_common) {
//        fprintf(f, "-sc_type_edge_common\n");
//    }
//    if ((sc_type_arc_access & type) == sc_type_arc_access) {
//        fprintf(f, "-sc_type_arc_access\n");
//    }
//    if ((sc_type_const & type) == sc_type_const) {
//        fprintf(f, "-sc_type_const\n");
//    }
//    if ((sc_type_var & type) == sc_type_var) {
//        fprintf(f, "-sc_type_var\n");
//    }
//    if ((sc_type_arc_pos & type) == sc_type_arc_pos) {
//        fprintf(f, "-sc_type_arc_pos\n");
//    }
//    if ((sc_type_arc_neg & type) == sc_type_arc_neg) {
//        fprintf(f, "-sc_type_arc_neg\n");
//    }
//    if ((sc_type_arc_fuz & type) == sc_type_arc_fuz) {
//        fprintf(f, "-sc_type_arc_fuz\n");
//    }
//    if ((sc_type_arc_perm & type) == sc_type_arc_perm) {
//        fprintf(f, "-sc_type_arc_perm\n");
//    }
//    if ((sc_type_node_tuple & type) == sc_type_node_tuple) {
//        fprintf(f, "-sc_type_node_tuple\n");
//    }
//    if ((sc_type_node_role & type) == sc_type_node_role) {
//        fprintf(f, "-sc_type_node_role\n");
//    }
//    if ((sc_type_node_norole & type) == sc_type_node_norole) {
//        fprintf(f, "-sc_type_node_norole\n");
//    }
//    if ((sc_type_node_class & type) == sc_type_node_class) {
//        fprintf(f, "-sc_type_node_class\n");
//    }
//    if ((sc_type_node_abstract & type) == sc_type_node_abstract) {
//        fprintf(f, "-sc_type_node_abstract\n");
//    }
//    if ((sc_type_node_material & type) == sc_type_node_material) {
//        fprintf(f, "-sc_type_node_material\n");
//    }
//    if ((sc_type_arc_pos_var_perm & type) == sc_type_arc_pos_var_perm) {
//        fprintf(f, "-sc_type_arc_pos_var_perm\n");
//    }

    return answer;
}

bool isAddrExist(sc_addr addr) {
    bool answer = false;
    for (int i = 0; i < nodeVector.size(); i++) {
        if (addr.offset == nodeVector.at(i).get_addr().offset && addr.seg == nodeVector.at(i).get_addr().seg) {
            answer = true;
            return answer;
        }
    }
    return answer;
}

int getIdByAddr(sc_addr addr) {
    for (int i = 0; i < nodeVector.size(); i++) {
        if (addr.offset == nodeVector.at(i).get_addr().offset && addr.seg == nodeVector.at(i).get_addr().seg) {
            return nodeVector.at(i).get_Id();
        }
    }
    return -1;
}

int main()
{
    sc_memory_params params;
    sc_memory_params_clear(&params);
    params.repo_path = "/home/artsiom/work/ostis/kb.bin";
    params.config_file = "/home/artsiom/work/ostis/config/sc-web.ini";
    params.ext_path = "/home/artsiom/work/ostis/sc-machine/bin/extensions";
    params.clear = SC_FALSE;
    sc_memory_initialize(&params);
    context = sc_memory_context_new(sc_access_lvl_make_max);
    uniqId = 0;
    f = fopen("/home/artsiom/Desktop/KnowledgeDump.txt", "w");
    run_test();
    fclose(f);
    sc_memory_context_free(context);
    sc_memory_shutdown(SC_TRUE);

    return 0;
}
