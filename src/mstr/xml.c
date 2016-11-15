#include <mstr/xml.h>
#include <utils/file_utils.h>

#ifdef __cplusplus
extern "C" {
#endif

#define XML_STATE_NONE 0
#define XML_STATE_TRY_READ_NODE_NAME 1
#define XML_STATE_READING_NODE_NAME 2
#define XML_STATE_TRY_READ_ATTRIBUTE_NAME 3
#define XML_STATE_READING_ATTRIBUTE_NAME 4
#define XML_STATE_TRY_READ_ATTRIBUTE_VALUE 5
#define XML_STATE_READING_ATTRIBUTE_VALUE 6
#define XML_STATE_TRY_READ_NEXT_NODE 7

#define XML_PARSE_LOG 0

/*

  function cat_char used in this function is not really efficient with big input
  because of cs[2] will cause function realloc inside cat_char working badly

  TODO need improved !

*/
void parse_xml_file(const char* path, lambda_ref* begin_func, lambda_ref* text_func, lambda_ref* end_func)
{
  FILE* file = open_file(path);
  if(!file) goto end;
  m_list* node_stacks = linked_list_new();
  m_string* current_text = new_string();
  m_list* current_attributes = linked_list_new();
  m_string* current_node_value = new_string();
  int state = XML_STATE_NONE;
  char c;

  #if XML_PARSE_LOG
  int tab = 0;
  #endif
  int depth = 0;
  int value_white = 1;
  char cs[2] = {'\0','\0'};
  while((c = fgetc(file)) != EOF)
  {
    cs[0] = c;
    switch (state)
    {
      case XML_STATE_NONE:
        if(c == '<')
        {
          state = XML_STATE_TRY_READ_NODE_NAME;
        }
        break;
      case XML_STATE_TRY_READ_NEXT_NODE:
        if(c == '<')
        {
          state = XML_STATE_TRY_READ_NODE_NAME;
          if(value_white)
          {
            current_node_value->func->release(current_node_value);
            current_node_value = new_string();
          }

          #if XML_PARSE_LOG == 1
          for(int i = 0; i < tab-1; i++) printf("\t");
          printf("value : %s\n",current_node_value->content);
          current_node_value->func->release(current_node_value);
          current_node_value = new_string();
          #endif

          if(text_func) text_func->callback(depth - 1, ((m_string*)node_stacks->func->get_last(node_stacks)), current_node_value);

          value_white = 1;
        }
        else
        {
          if(c == '>')
          {
            value_white = 1;
            current_node_value->func->release(current_node_value);
            current_node_value = new_string();
          }
          else
          {
            if(c != ' ' && c != '\t' && c != '\n') value_white = 0;
            current_node_value->func->cat_char(current_node_value, cs);
          }
        }
        break;
      case XML_STATE_TRY_READ_NODE_NAME:
        if(c != ' ' || c != '\t' || c != '\n')
        {
          if(c == '/')
          {
            #if XML_PARSE_LOG == 1
            tab--;
            for(int i = 0; i < tab; i++) printf("\t");
            printf("end node: %s\n",((m_string*)node_stacks->func->get_last(node_stacks))->content);
            #endif
            depth = depth - 1;
            if(end_func) end_func->callback(depth,((m_string*)node_stacks->func->get_last(node_stacks)));
            // remove from stack
            m_string* str = ((m_string*)node_stacks->func->get_last(node_stacks));
            node_stacks->func->pop(node_stacks);
            str->func->release(str);

            if(node_stacks->size == 0) state = XML_STATE_NONE;
            else state = XML_STATE_TRY_READ_NEXT_NODE;
            while(current_attributes->size)
            {
              m_string* attr = ((m_string*)current_attributes->func->get_last(current_attributes));
              attr->func->release(attr);
              current_attributes->func->pop(current_attributes);
            }
          }
          else
          {
            current_text = new_string();
            current_text->func->cat_char(current_text, cs);

            state = XML_STATE_READING_NODE_NAME;
          }
        }
        break;
      case XML_STATE_READING_NODE_NAME:
        if(c != ' ' && c != '\t' && c != '\n')
        {
          if(c == '>')
          {
            node_stacks->func->push(node_stacks, current_text, 1);
            #if XML_PARSE_LOG == 1
            for(int i = 0; i < tab; i++) printf("\t");
            printf("begin node: %s\n",((m_string*)node_stacks->func->get_last(node_stacks))->content);
            tab++;
            #endif
            if(begin_func) begin_func->callback(depth, ((m_string*)node_stacks->func->get_last(node_stacks)), current_attributes);
            depth = depth + 1;
            state = XML_STATE_TRY_READ_NEXT_NODE;

            while(current_attributes->size)
            {
              m_string* attr = ((m_string*)current_attributes->func->get_last(current_attributes));
              attr->func->release(attr);
              current_attributes->func->pop(current_attributes);
            }
          }
          else if(c == '/' || c == '?')
          {
            node_stacks->func->push(node_stacks, current_text, 1);

            #if XML_PARSE_LOG == 1
            for(int i = 0; i < tab; i++) printf("\t");
            printf("begin node: %s\n",((m_string*)node_stacks->func->get_last(node_stacks))->content);
            tab++;
            tab--;
            for(int i = 0; i < tab; i++) printf("\t");
            printf("end node: %s\n",((m_string*)node_stacks->func->get_last(node_stacks))->content);
            #endif

            if(begin_func) begin_func->callback(depth, ((m_string*)node_stacks->func->get_last(node_stacks)), current_attributes);
            if(end_func) end_func->callback(depth, ((m_string*)node_stacks->func->get_last(node_stacks)));
            // remove from stack
            m_string* str = ((m_string*)node_stacks->func->get_last(node_stacks));
            node_stacks->func->pop(node_stacks);
            str->func->release(str);

            if(node_stacks->size == 0) state = XML_STATE_NONE;
            else state = XML_STATE_TRY_READ_NEXT_NODE;

            while(current_attributes->size)
            {
              m_string* attr = ((m_string*)current_attributes->func->get_last(current_attributes));
              attr->func->release(attr);
              current_attributes->func->pop(current_attributes);
            }
          }
          else
          {
              current_text->func->cat_char(current_text, cs);
          }
        }
        else
        {
          node_stacks->func->push(node_stacks, current_text, 1);
          current_text = new_string();

          state = XML_STATE_TRY_READ_ATTRIBUTE_NAME;
        }
        break;
      case XML_STATE_TRY_READ_ATTRIBUTE_NAME:
        if(c != ' ' && c != '\t' && c!= '\n')
        {
          if(c == '/' || c == '?')
          {
            #if XML_PARSE_LOG == 1
            for(int i = 0; i < tab; i++) printf("\t");
            printf("begin node: %s\n",((m_string*)node_stacks->func->get_last(node_stacks))->content);
            tab++;
            tab--;
            for(int i = 0; i < tab; i++) printf("\t");
            printf("end node: %s\n",((m_string*)node_stacks->func->get_last(node_stacks))->content);
            #endif

            if(begin_func) begin_func->callback(depth, ((m_string*)node_stacks->func->get_last(node_stacks)), current_attributes);
            if(end_func) end_func->callback(depth, ((m_string*)node_stacks->func->get_last(node_stacks)));
            // remove from stack
            m_string* str = ((m_string*)node_stacks->func->get_last(node_stacks));
            node_stacks->func->pop(node_stacks);
            str->func->release(str);

            if(node_stacks->size == 0) state = XML_STATE_NONE;
            else state = XML_STATE_TRY_READ_NEXT_NODE;

            while(current_attributes->size)
            {
              m_string* attr = ((m_string*)current_attributes->func->get_last(current_attributes));
              attr->func->release(attr);
              current_attributes->func->pop(current_attributes);
            }
          }
          else if(c == '>')
          {
            //begin_func
            #if XML_PARSE_LOG == 1
            for(int i = 0; i < tab; i++) printf("\t");
            printf("begin node: %s\n",((m_string*)node_stacks->func->get_last(node_stacks))->content);
            tab++;
            #endif
            if(begin_func) begin_func->callback(depth, ((m_string*)node_stacks->func->get_last(node_stacks)), current_attributes);
            depth = depth + 1;

            state = XML_STATE_TRY_READ_NEXT_NODE;

            while(current_attributes->size)
            {
              m_string* attr = ((m_string*)current_attributes->func->get_last(current_attributes));
              attr->func->release(attr);
              current_attributes->func->pop(current_attributes);
            }
          }
          else
          {
            current_text = new_string();
            current_text->func->cat_char(current_text, cs);

            state = XML_STATE_READING_ATTRIBUTE_NAME;
          }
        }
        break;
      case XML_STATE_READING_ATTRIBUTE_NAME:
        if(c != ' ' && c != '\t' && c != '\n')
        {
          if(c == '=')
          {
            current_attributes->func->push(current_attributes, current_text, 1);
            current_text = new_string();

            state = XML_STATE_TRY_READ_ATTRIBUTE_VALUE;
          }
          else
          {
              current_text->func->cat_char(current_text, cs);
          }
        }
        else
        {
          //TODO error
        }
        break;
      case XML_STATE_TRY_READ_ATTRIBUTE_VALUE:
        if(c == '\"')
        {
          state = XML_STATE_READING_ATTRIBUTE_VALUE;
        }
        break;
      case XML_STATE_READING_ATTRIBUTE_VALUE:
        if(c == '\"')
        {
          current_attributes->func->push(current_attributes, current_text, 1);
          current_text = new_string();

          state = XML_STATE_TRY_READ_ATTRIBUTE_NAME;
        }
        else
        {
            current_text->func->cat_char(current_text, cs);
        }
        break;
      default:
        break;
    }
  }

  fclose(file);
  end:;
}

m_string* m_xml_get_value(m_list* attributes, char* name)
{
  for(int i = 0; i < attributes->size; i += 2)
  {
    m_string* attr_name = (m_string*)attributes->func->get_index(attributes, i);
    m_string* attr_value = (m_string*)attributes->func->get_index(attributes, i + 1);
    if(strcmp(attr_name->content, name) == 0) return attr_value;
  }
  return 0;
}

#ifdef __cplusplus
}
#endif
