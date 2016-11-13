#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mstr/string.h>
#include <utils/file_utils.h>
#include <ctype.h>
#include <string.h>
#include <mstr/list.h>

m_string* template_folder = 0;

void generate_new_file(int argc, char const *argv[])
{
  m_string* struct_name = new_string();
  struct_name->func->cat_char(struct_name, argv[1]);
  m_string* struct_name_uppercase = new_string_from_str(struct_name);
  struct_name_uppercase->func->to_uppercase(struct_name_uppercase);

  m_string* struct_parent_name = new_string();
  struct_parent_name->func->cat_char(struct_parent_name, argv[2]);
  m_string* struct_parent_name_uppercase = new_string_from_str(struct_parent_name);
  struct_parent_name_uppercase->func->to_uppercase(struct_parent_name_uppercase);

  m_string* header_location = new_string();
  header_location->func->cat_char(header_location, argv[3]);

  m_string* source_location = new_string();
  source_location->func->cat_char(source_location, argv[4]);

  m_string* header_template_file = new_string_from_str(template_folder);
  if(header_template_file->content[header_template_file->length - 1] == '/')
  {
    header_template_file->func->cat_char(header_template_file, "header_template.txt");
  }
  else
  {
    header_template_file->func->cat_char(header_template_file, "/header_template.txt");
  }
  m_string* header_template = read_string_from_file(header_template_file->content);
  m_string* source_template_file = new_string_from_str(template_folder);
  if(source_template_file->content[source_template_file->length - 1] == '/')
  {
    source_template_file->func->cat_char(source_template_file, "source_template.txt");
  }
  else
  {
    source_template_file->func->cat_char(source_template_file, "/source_template.txt");
  }
  m_string* source_template = read_string_from_file(source_template_file->content);

  //--------------------------------------------------------------------------------------

  header_template->func->replace_str(header_template, new_string_from_char("[struct_name]"), struct_name);
  header_template->func->replace_str(header_template, new_string_from_char("[struct_name_uppercase]"), struct_name_uppercase);
  header_template->func->replace_str(header_template, new_string_from_char("[struct_parent_name]"), struct_parent_name);
  header_template->func->replace_str(header_template, new_string_from_char("[struct_parent_name_uppercase]"), struct_parent_name_uppercase);

  source_template->func->replace_str(source_template, new_string_from_char("[struct_name]"), struct_name);
  source_template->func->replace_str(source_template, new_string_from_char("[struct_name_uppercase]"), struct_name_uppercase);
  source_template->func->replace_str(source_template, new_string_from_char("[struct_parent_name]"), struct_parent_name);
  source_template->func->replace_str(source_template, new_string_from_char("[struct_parent_name_uppercase]"), struct_parent_name_uppercase);

  m_string* struct_parent_name_init = new_string();
  if(strcmp(struct_parent_name->content, "ref") != 0)
  {

    struct_parent_name_init->func->cat_str(struct_parent_name_init, struct_parent_name);
    struct_parent_name_init->func->cat_char(struct_parent_name_init,"_init(node);");
  }
  source_template->func->replace_str(source_template, new_string_from_char("[struct_parent_name_init]"), struct_parent_name_init);

  m_string* child_function_declaration = new_string();
  m_string* struct_function_interface_declaration = new_string();
  m_string* struct_function_interface_assignment = new_string();

  m_string* implement_function = new_string();

  printf("Enter child functions (e.g int func_name arg1 arg2) : \n");
  char buff[100];
  m_list* params = array_list_new();
  while(1)
  {
    scanf ("%[^\n]%*c", buff);
    if(strcmp(buff, "q") == 0)
    {
      printf("\r\033[A \n");
      break;
    }
    else
    {
      char* ch;
      char s[2] = " ";
      ch = strtok(buff, s);
      int add = -1;
      while(ch != NULL)
      {
        if(add == -1)
        {
          if(strcmp(ch,"add") == 0) add = 1;
          else add = 0;
        }
        else
        {
          params->func->push(params, new_string_from_char(ch), 1);
        }
        ch = strtok(NULL, s);
      }
      if(add == 1) child_function_declaration->func->cat_char(child_function_declaration,"\n");
      struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,"\n");
      struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment,"\n");
      implement_function->func->cat_char(implement_function, "\n\n");

      for(int i = 0; i < params->size; i++)
      {
        if(i == 0)
        {
          if(add == 1) child_function_declaration->func->cat_char(child_function_declaration,"\t");
          if(add == 1) child_function_declaration->func->cat_str(child_function_declaration, params->func->get_index(params, i));
          struct_function_interface_declaration->func->cat_str(struct_function_interface_declaration, params->func->get_index(params, i));
          implement_function->func->cat_str(implement_function, params->func->get_index(params, i));
        }
        else if(i == 1)
        {
          if(add == 1) child_function_declaration->func->cat_char(child_function_declaration, "(*");
          if(add == 1) child_function_declaration->func->cat_str(child_function_declaration, params->func->get_index(params, i));
          if(add == 1) child_function_declaration->func->cat_char(child_function_declaration, ")();");

          struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration," ");
          struct_function_interface_declaration->func->cat_str(struct_function_interface_declaration, struct_name);
          struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,"_");
          struct_function_interface_declaration->func->cat_str(struct_function_interface_declaration, params->func->get_index(params, i));
          struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,"(");
          if(i == params->size - 1)
          {
            struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,");");
          }

          implement_function->func->cat_char(implement_function, " ");
          implement_function->func->cat_str(implement_function, struct_name);
          implement_function->func->cat_char(implement_function, "_");
          implement_function->func->cat_str(implement_function, params->func->get_index(params, i));
          implement_function->func->cat_char(implement_function, "(");
          if(i == params->size - 1)
          {
            implement_function->func->cat_char(implement_function,")\n{\n\t//TODO implement\n}");
          }

          struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment, "\t.");
          struct_function_interface_assignment->func->cat_str(struct_function_interface_assignment, params->func->get_index(params, i));
          struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment, " = ");
          struct_function_interface_assignment->func->cat_str(struct_function_interface_assignment, struct_name);
          struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment, "_");
          struct_function_interface_assignment->func->cat_str(struct_function_interface_assignment, params->func->get_index(params, i));
          struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment, ",");
        }
        else
        {
            if(i > 2)
            {
              struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,", ");
            }
            struct_function_interface_declaration->func->cat_str(struct_function_interface_declaration, params->func->get_index(params, i));
            struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration," arg_");
            char i_to_s[10];
            snprintf(i_to_s, sizeof(i_to_s), "%d", i-2);
            struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration, i_to_s);
            if(i == params->size - 1)
            {
              struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,");");
            }

            if(i > 2)
            {
              implement_function->func->cat_char(implement_function, ", ");
            }
            implement_function->func->cat_str(implement_function, params->func->get_index(params, i));
            implement_function->func->cat_char(implement_function, " arg_");
            implement_function->func->cat_char(implement_function, i_to_s);
            if(i == params->size - 1)
            {
              implement_function->func->cat_char(implement_function,")\n{\n\t//TODO implement\n}");
            }
        }
      }
      if(add == 1) child_function_declaration->func->cat_char(child_function_declaration," \\");
      struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment," \\");
    }
    params->func->clear(params);
  }
  header_template->func->replace_str(header_template, new_string_from_char("[child_function_declaration]"), child_function_declaration);
  header_template->func->replace_str(header_template, new_string_from_char("[struct_function_interface_declaration]"), struct_function_interface_declaration);
  header_template->func->replace_str(header_template, new_string_from_char("[struct_function_interface_assignment]"), struct_function_interface_assignment);

  source_template->func->replace_str(source_template, new_string_from_char("[implement_function]"), implement_function);

  m_string* child_field_declaration = new_string();
  printf("Enter child fields: \n");
  while(1)
  {
    scanf ("%[^\n]%*c", buff);
    if(strcmp(buff, "q") == 0)
    {
      printf("\r\033[A \n");
      break;
    }
    else
    {
      child_field_declaration->func->cat_char(child_field_declaration, "\n\t");
      child_field_declaration->func->cat_char(child_field_declaration, buff);
      child_field_declaration->func->cat_char(child_field_declaration, "; \\");
    }
  }
  header_template->func->replace_str(header_template, new_string_from_char("[child_field_declaration]"), child_field_declaration);

  FILE* file = fopen(header_location->content, "w");
  if(file)
  {
    fputs(header_template->content, file);
    fclose(file);
  }

  file = fopen(source_location->content, "w");
  if(file)
  {
    fputs(source_template->content, file);
    fclose(file);
  }
}

void modify_file(int argc, char const *argv[])
{
  m_string* struct_name = new_string();
  struct_name->func->cat_char(struct_name, argv[1]);
  m_string* struct_name_uppercase = new_string_from_str(struct_name);
  struct_name_uppercase->func->to_uppercase(struct_name_uppercase);

  m_string* struct_parent_name = new_string();
  struct_parent_name->func->cat_char(struct_parent_name, argv[2]);
  m_string* struct_parent_name_uppercase = new_string_from_str(struct_parent_name);
  struct_parent_name_uppercase->func->to_uppercase(struct_parent_name_uppercase);

  m_string* header_location = new_string();
  header_location->func->cat_char(header_location, argv[3]);

  m_string* source_location = new_string();
  source_location->func->cat_char(source_location, argv[4]);

  m_string* current_header_content = read_string_from_file(header_location->content);
  m_string* current_source_content = read_string_from_file(source_location->content);

  m_string* child_function_declaration = new_string();
  m_string* struct_function_interface_declaration = new_string();
  m_string* struct_function_interface_assignment = new_string();

  m_string* implement_function = new_string();

  printf("Enter child functions (e.g int func_name arg1 arg2) : \n");
  char buff[100];
  m_list* params = array_list_new();
  while(1)
  {
    scanf ("%[^\n]%*c", buff);
    if(strcmp(buff, "q") == 0)
    {
      printf("\r\033[A \n");
      break;
    }
    else
    {
      char* ch;
      char s[2] = " ";
      ch = strtok(buff, s);
      int add = -1;
      while(ch != NULL)
      {
        if(add == -1)
        {
          if(strcmp(ch,"add") == 0) add = 1;
          else add = 0;
        }
        else
        {
          params->func->push(params, new_string_from_char(ch), 1);
        }
        ch = strtok(NULL, s);
      }

      if(params->size >= 2)
      {
        m_string* tmp_str = new_string();
        tmp_str->func->cat_char(tmp_str," ");
        tmp_str->func->cat_str(tmp_str, struct_name);
        tmp_str->func->cat_char(tmp_str,"_");
        tmp_str->func->cat_str(tmp_str, params->func->get_index(params, 1));
        tmp_str->func->cat_char(tmp_str,"(");
        if(current_header_content->func->contain_str(current_header_content, tmp_str))
        {
          tmp_str->func->release(tmp_str);
          params->func->clear(params);
          continue;
        }
        tmp_str->func->release(tmp_str);
      }
      else
      {
        params->func->clear(params);
        continue;
      }

      if(add == 1) child_function_declaration->func->cat_char(child_function_declaration,"\n");
      struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,"\n");
      struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment,"\n");
      implement_function->func->cat_char(implement_function, "\n\n");

      for(int i = 0; i < params->size; i++)
      {
        if(i == 0)
        {
          if(add == 1) child_function_declaration->func->cat_char(child_function_declaration,"\t");
          if(add == 1) child_function_declaration->func->cat_str(child_function_declaration, params->func->get_index(params, i));
          struct_function_interface_declaration->func->cat_str(struct_function_interface_declaration, params->func->get_index(params, i));
          implement_function->func->cat_str(implement_function, params->func->get_index(params, i));
        }
        else if(i == 1)
        {
          if(add == 1) child_function_declaration->func->cat_char(child_function_declaration, "(*");
          if(add == 1) child_function_declaration->func->cat_str(child_function_declaration, params->func->get_index(params, i));
          if(add == 1) child_function_declaration->func->cat_char(child_function_declaration, ")();");

          struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration," ");
          struct_function_interface_declaration->func->cat_str(struct_function_interface_declaration, struct_name);
          struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,"_");
          struct_function_interface_declaration->func->cat_str(struct_function_interface_declaration, params->func->get_index(params, i));
          struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,"(");
          if(i == params->size - 1)
          {
            struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,");");
          }

          implement_function->func->cat_char(implement_function, " ");
          implement_function->func->cat_str(implement_function, struct_name);
          implement_function->func->cat_char(implement_function, "_");
          implement_function->func->cat_str(implement_function, params->func->get_index(params, i));
          implement_function->func->cat_char(implement_function, "(");
          if(i == params->size - 1)
          {
            implement_function->func->cat_char(implement_function,")\n{\n\t//TODO implement\n}");
          }

          struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment, "\t.");
          struct_function_interface_assignment->func->cat_str(struct_function_interface_assignment, params->func->get_index(params, i));
          struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment, " = ");
          struct_function_interface_assignment->func->cat_str(struct_function_interface_assignment, struct_name);
          struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment, "_");
          struct_function_interface_assignment->func->cat_str(struct_function_interface_assignment, params->func->get_index(params, i));
          struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment, ",");
        }
        else
        {
            if(i > 2)
            {
              struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,", ");
            }
            struct_function_interface_declaration->func->cat_str(struct_function_interface_declaration, params->func->get_index(params, i));
            struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration," arg_");
            char i_to_s[10];
            snprintf(i_to_s, sizeof(i_to_s), "%d", i-2);
            struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration, i_to_s);
            if(i == params->size - 1)
            {
              struct_function_interface_declaration->func->cat_char(struct_function_interface_declaration,");");
            }

            if(i > 2)
            {
              implement_function->func->cat_char(implement_function, ", ");
            }
            implement_function->func->cat_str(implement_function, params->func->get_index(params, i));
            implement_function->func->cat_char(implement_function, " arg_");
            implement_function->func->cat_char(implement_function, i_to_s);
            if(i == params->size - 1)
            {
              implement_function->func->cat_char(implement_function,")\n{\n\t//TODO implement\n}");
            }
        }
      }
      if(add == 1) child_function_declaration->func->cat_char(child_function_declaration," \\");
      struct_function_interface_assignment->func->cat_char(struct_function_interface_assignment," \\");
    }
    params->func->clear(params);
  }

  m_string* child_function_declaration_target = new_string_from_char("/*EXPAND FUNCTION -- DO NOT DELETE IT*/ \\");
  child_function_declaration_target->func->cat_str(child_function_declaration_target, child_function_declaration);
  current_header_content->func->replace_str(current_header_content, new_string_from_char("/*EXPAND FUNCTION -- DO NOT DELETE IT*/ \\"), child_function_declaration_target);

  m_string* struct_function_interface_declaration_target = new_string_from_char("/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/");
  struct_function_interface_declaration_target->func->cat_str(struct_function_interface_declaration_target, struct_function_interface_declaration);
  current_header_content->func->replace_str(current_header_content, new_string_from_char("/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/"), struct_function_interface_declaration_target);

  m_string* struct_function_interface_assignment_target = new_string_from_char("/*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \\");
  struct_function_interface_assignment_target->func->cat_str(struct_function_interface_assignment_target, struct_function_interface_assignment);
  current_header_content->func->replace_str(current_header_content, new_string_from_char("/*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \\"), struct_function_interface_assignment_target);

  m_string* implement_function_target = new_string_from_char("/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/");
  implement_function_target->func->cat_str(implement_function_target, implement_function);
  current_source_content->func->replace_str(current_source_content, new_string_from_char("/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/"), implement_function_target);

  m_string* child_field_declaration = new_string();
  printf("Enter child fields: \n");
  while(1)
  {
    scanf ("%[^\n]%*c", buff);
    if(strcmp(buff, "q") == 0)
    {
      printf("\r\033[A \n");
      break;
    }
    else
    {
      m_string* temp = new_string();
      temp->func->cat_char(temp, "\n\t");
      temp->func->cat_char(temp, buff);
      temp->func->cat_char(temp, "; \\");

      if(current_header_content->func->contain_str(current_header_content, temp))
      {
        temp->func->release(temp);
        continue;
      }
      child_field_declaration->func->cat_str(child_field_declaration, temp);
      temp->func->release(temp);
    }
  }

  m_string* child_field_declaration_target = new_string_from_char("/*EXPAND FIELD -- DO NOT DELETE IT*/ \\");
  child_field_declaration_target->func->cat_str(child_field_declaration_target, child_field_declaration);
  current_header_content->func->replace_str(current_header_content, new_string_from_char("/*EXPAND FIELD -- DO NOT DELETE IT*/ \\"), child_field_declaration_target);

  FILE* file = fopen(header_location->content, "w");
  if(file)
  {
    fputs(current_header_content->content, file);
    fclose(file);
  }

  file = fopen(source_location->content, "w");
  if(file)
  {
    fputs(current_source_content->content, file);
    fclose(file);
  }
}

int main(int argc, char const *argv[])
{
  char* fix[5];
  fix[0] = argv[0];
  int n_ok = 0;
  int p_ok = 0;
  int h_ok = 0;
  int c_ok = 0;
  int t_ok = 0;

  for(int i = 0; i < argc; i++)
  {
    char* s = argv[i];
    if(strcmp(s,"-n") == 0 && i + 1 < argc)
    {
      fix[1] = argv[i + 1];
      i++;
      n_ok = 1;
    }
    else if(strcmp(s,"-p") == 0 && i + 1 < argc)
    {
      fix[2] = argv[i + 1];
      i++;
      p_ok = 1;
    }
    else if(strcmp(s,"-h") == 0 && i + 1 < argc)
    {
      fix[3] = argv[i + 1];
      i++;
      h_ok = 1;
    }
    else if(strcmp(s,"-c") == 0 && i + 1 < argc)
    {
      fix[4] = argv[i + 1];
      i++;
      c_ok = 1;
    }
    else if(strcmp(s,"-t") == 0 && i + 1 < argc)
    {
      template_folder = new_string_from_char(argv[i + 1]);
      i++;
      t_ok = 1;
    }
  }

  if(!n_ok || !p_ok || !h_ok || !c_ok || !t_ok)
  {
    int p_length = strlen(argv[0]);
    printf("wrong arguments!\n");
    printf("%s", argv[0]);
    printf("  -n [struct name]\n");
    for(int i = 0; i < p_length; ++i) printf(" ");
    printf("  -p [struct parent name]\n");
    for(int i = 0; i < p_length; ++i) printf(" ");
    printf("  -h [header location to save]\n");
    for(int i = 0; i < p_length; ++i) printf(" ");
    printf("  -c [source location to save]\n");
    for(int i = 0; i < p_length; ++i) printf(" ");
    printf("  -t [template folder]\n");
    return 0;
  }

  struct stat st = {0};
  int header_file_exist = 0;
  int source_file_exist = 0;
  if (stat(fix[3], &st) != -1)
  {
    header_file_exist = 1;
  }
  if (stat(fix[4], &st) != -1)
  {
    source_file_exist = 1;
  }

  if(header_file_exist == 0 && source_file_exist == 1)
  {
    printf("no header file but has source file!\n please check\n");
    return 0;
  }

  if(header_file_exist == 1 && source_file_exist == 0)
  {
    printf("header file exist but has no source file!\n please check\n");
    return 0;
  }

  if(header_file_exist == 0 && source_file_exist == 0)
  {
    printf("generating file ...\n");
    generate_new_file(5, fix);
  }
  else
  {
    printf("modifing file ...\n");
    modify_file(5, fix);
  }

  ref_update_auto_release_pool();
  return 0;
}
