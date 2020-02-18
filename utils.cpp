extern "C" {
#include "sc_memory_headers.h"
#include "utils.h"
#include "sc_helper.h"
}

#include <stdio.h>
#include <iostream>


#define NUMBER_PRECISE 8

using namespace std;

void printEl(sc_memory_context *context, sc_addr element, FILE *f)
{
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
                sc_stream_free(stream);
                free(data);
            }
            else
            {
                fprintf(f, "%u|%u", element.seg, element.offset);
            }
        }
        catch (...) {
            fprintf(f, "%s", "fail");
        }
        return;
    }
    if ((sc_type_link & type) == sc_type_link) {
        fprintf(f, "[%s]", printContent(context, element));
        return;
    }
    if ((sc_type_arc_common & type) == sc_type_arc_common) {
        sc_addr elem1, elem2;
        sc_memory_get_arc_begin(context, element, &elem1);
        sc_memory_get_arc_end(context, element, &elem2);
        fprintf(f, "(");
        printEl(context, elem1, f);
        fprintf(f, " => ");
        printEl(context, elem2,f);
        fprintf(f, ")");
        return;
    }
    if ((sc_type_arc_pos_const_perm & type) == sc_type_arc_pos_const_perm) {
        sc_addr elem1, elem2;
        sc_memory_get_arc_begin(context, element, &elem1);
        sc_memory_get_arc_end(context, element, &elem2);
        fprintf(f, "(");
        printEl(context, elem1, f);
        fprintf(f, " -> ");
        printEl(context, elem2,f);
        fprintf(f, ")");
        return;
    }
    fprintf(f, "unknowElement");
    if ((sc_type_edge_common & type) == sc_type_edge_common) {
        fprintf(f, "-sc_type_edge_common\n");
    }
    if ((sc_type_arc_access & type) == sc_type_arc_access) {
        fprintf(f, "-sc_type_arc_access\n");
    }
    if ((sc_type_const & type) == sc_type_const) {
        fprintf(f, "-sc_type_const\n");
    }
    if ((sc_type_var & type) == sc_type_var) {
        fprintf(f, "-sc_type_var\n");
    }
    if ((sc_type_arc_pos & type) == sc_type_arc_pos) {
        fprintf(f, "-sc_type_arc_pos\n");
    }
    if ((sc_type_arc_neg & type) == sc_type_arc_neg) {
        fprintf(f, "-sc_type_arc_neg\n");
    }
    if ((sc_type_arc_fuz & type) == sc_type_arc_fuz) {
        fprintf(f, "-sc_type_arc_fuz\n");
    }
    if ((sc_type_arc_perm & type) == sc_type_arc_perm) {
        fprintf(f, "-sc_type_arc_perm\n");
    }
    if ((sc_type_node_tuple & type) == sc_type_node_tuple) {
        fprintf(f, "-sc_type_node_tuple\n");
    }
    if ((sc_type_node_role & type) == sc_type_node_role) {
        fprintf(f, "-sc_type_node_role\n");
    }
    if ((sc_type_node_norole & type) == sc_type_node_norole) {
        fprintf(f, "-sc_type_node_norole\n");
    }
    if ((sc_type_node_class & type) == sc_type_node_class) {
        fprintf(f, "-sc_type_node_class\n");
    }
    if ((sc_type_node_abstract & type) == sc_type_node_abstract) {
        fprintf(f, "-sc_type_node_abstract\n");
    }
    if ((sc_type_node_material & type) == sc_type_node_material) {
        fprintf(f, "-sc_type_node_material\n");
    }
    if ((sc_type_arc_pos_var_perm & type) == sc_type_arc_pos_var_perm) {
        fprintf(f, "-sc_type_arc_pos_var_perm\n");
    }


}

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

int getInt(sc_memory_context *context, sc_addr element)
{
    int res = 0;
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data;
    if (SC_RESULT_OK != sc_memory_get_link_content(context, element, &stream))
    {
        printf("Can't read content\n");
        return -1;
    }
    sc_stream_get_length(stream, &length);
    data = (sc_char *)calloc(length + 1, sizeof(sc_char));
    sc_stream_read_data(stream, data, length, &read_length);
    data[length] = '\0';

    res = atoi(data);

    sc_stream_free(stream);
    free(data);
    return res;
}

int getFloat(sc_memory_context *context, sc_addr element)
{
    int res = 0;
    sc_stream *stream;
    sc_uint32 length = 0, read_length = 0;
    sc_char *data;
    if (SC_RESULT_OK != sc_memory_get_link_content(context, element, &stream))
    {
        printf("Can't read content\n");
        return -1;
    }
    sc_stream_get_length(stream, &length);
    data = (sc_char *)calloc(length + 1, sizeof(sc_char));
    sc_stream_read_data(stream, data, length, &read_length);
    data[length] = '\0';

    res = atof(data);

    sc_stream_free(stream);
    free(data);
    return res;
}

sc_addr genIntNode(sc_memory_context *context, sc_uint32 data)
{
    sc_stream *stream;
    sc_addr link;
    char *content = (char *)calloc(NUMBER_PRECISE, sizeof(sc_char));
    snprintf(content, NUMBER_PRECISE, "%d", data);

    link = sc_memory_link_new(context);
    stream = sc_stream_memory_new(content, strlen(content), SC_STREAM_FLAG_READ, SC_FALSE);
    if (SC_RESULT_OK != sc_memory_set_link_content(context, link, stream))
    {
        free(content);
        sc_memory_element_free(context, link);
        SC_ADDR_MAKE_EMPTY(link);
        sc_stream_free(stream);
        return link;
    }
    free(content);
    sc_stream_free(stream);
    return link;
}

sc_addr genFloatNode(sc_memory_context *context, float data)
{
    sc_stream *stream;
    sc_addr link;
    char *content = (char *)calloc(NUMBER_PRECISE, sizeof(sc_char));
    snprintf(content, NUMBER_PRECISE, "%f", data);

    link = sc_memory_link_new(context);
    stream = sc_stream_memory_new(content, strlen(content), SC_STREAM_FLAG_READ, SC_FALSE);
    if (SC_RESULT_OK != sc_memory_set_link_content(context, link, stream))
    {
        free(content);
        sc_memory_element_free(context, link);
        SC_ADDR_MAKE_EMPTY(link);
        sc_stream_free(stream);
        return link;
    }
    free(content);
    sc_stream_free(stream);
    return link;
}
