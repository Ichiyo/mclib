#include <graphic/skin3d/m_skin_node_parser.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <graphic/skin3d/m_skin_node.h>
#include <utils/file_utils.h>
#include <mstr/xml.h>
#include <mstr/list.h>
#include <mstr/string.h>
#include <graphic/skin3d/m_controller_skin.h>
#include <graphic/skin3d/m_geometry_mesh.h>
#include <graphic/skin3d/m_skin_join.h>
#include <graphic/skin3d/m_visual_scene_join.h>
#include <graphic/skin3d/m_visual_scene_node.h>
#include <mstr/lambda.h>

m_list* m_skin_node_parser_parse(char* path)
{
  __assignable m_list* geometry_meshs = array_list_new();
  __assignable m_list* controller_skins = array_list_new();
  __assignable m_list* visual_nodes = array_list_new();

  __assignable int parsing_geometry_mesh = 0;
  __assignable int parsing_vertices = 0;
  __assignable int parsing_polylist = 0;

  __assignable int parsing_controller = 0;
  __assignable m_float_array* last_float_array = 0;

  __assignable int parsing_visual_scene = 0;
  __assignable int start_join = 0;
  // m_skin_join* current_join = 0;
  __assignable m_visual_scene_join* current_join = 0;
  __assignable m_visual_scene_node* current_node = 0;
  __assignable int is_node = 0;

  /********************************************
  *           prepare collada data
  *********************************************/
  parse_xml_file(path,

    SAFE_NEW_LAMBDA(void, (int depth, m_string* name, m_list* attributes)
    {
      if(strcmp(name->content, "geometry") == 0)
      {
        parsing_geometry_mesh = 1;
        m_geometry_mesh* gm = m_geometry_mesh_new();
        _(gm->id,cat_str, m_xml_get_value(attributes, "id"));
        _(gm->name,cat_str, m_xml_get_value(attributes, "name"));
        _(geometry_meshs, push, gm, 1);
      }
      else if(parsing_geometry_mesh)
      {
        m_geometry_mesh* gm = _(geometry_meshs,get_last);
        if(strcmp(name->content, "source") == 0)
        {
          m_mesh_source* source = m_mesh_source_new();
          source->source_id->func->cat_str(source->source_id, m_xml_get_value(attributes,"id"));
          gm->func->add_source(gm, source);
        }
        else if(strcmp(name->content, "float_array") == 0)
        {
          m_mesh_source* source = gm->sources->func->get_last(gm->sources);
          source->farr_id->func->cat_str(source->farr_id, m_xml_get_value(attributes, "id"));
        }
        else if(strcmp(name->content, "accessor") == 0)
        {
          m_mesh_source* source = gm->sources->func->get_last(gm->sources);
          sscanf(m_xml_get_value(attributes, "count")->content, "%d", &source->count);
          sscanf(m_xml_get_value(attributes, "stride")->content, "%d", &source->stride);
        }
        else if(strcmp(name->content, "vertices") == 0)
        {
          m_mesh_vertices* vertices = m_mesh_vertices_new();
          vertices->id->func->cat_str(vertices->id, m_xml_get_value(attributes, "id"));
          gm->func->set_vertices(gm, vertices);
          parsing_vertices = 1;
        }
        else if(strcmp(name->content, "polylist") == 0)
        {
          m_mesh_polylist* polylist = m_mesh_polylist_new();
          gm->func->set_polylist(gm, polylist);
          parsing_polylist = 1;
        }

        if(parsing_polylist)
        {
          m_mesh_polylist* polylist = gm->polylist;
          if(strcmp(name->content, "input") == 0)
          {
            int offset;
            sscanf(m_xml_get_value(attributes, "offset")->content, "%d", &offset);
            m_string* semantic = m_xml_get_value(attributes, "semantic");
            char* target_source = m_xml_get_value(attributes, "source")->content + 1;
            int added = 0;
            for(unsigned int i = 0; i < gm->sources->size; i++)
            {
              m_mesh_source* source = gm->sources->func->get_index(gm->sources, i);
              if(strcmp(source->source_id->content, target_source) == 0)
              {
                polylist->func->add_source(polylist, source, new_string_from_str(semantic), offset);
                added = 1;
                break;
              }
            }
            if(!added)
            {
              if(strcmp(gm->vertices->id->content, target_source) == 0)
              {
                polylist->func->add_source(polylist, gm->vertices->source, new_string_from_str(semantic), offset);
              }
            }
          }
        }

        if(parsing_vertices)
        {
          if(strcmp(name->content, "input") == 0)
          {
            m_mesh_vertices* vertices = gm->vertices;
            vertices->semantic->func->cat_str(vertices->semantic, m_xml_get_value(attributes, "semantic"));
            char* target_source = m_xml_get_value(attributes, "source")->content + 1;
            for(unsigned int i = 0; i < gm->sources->size; i++)
            {
              m_mesh_source* source = gm->sources->func->get_index(gm->sources, i);
              if(strcmp(source->source_id->content, target_source) == 0)
              {
                vertices->func->add_source(vertices, source);
                break;
              }
            }
          }
        }
      }
      else if(strcmp(name->content, "controller") == 0)
      {
        parsing_controller = 1;
        m_controller_skin* cs = m_controller_skin_new();
        controller_skins->func->push(controller_skins, cs, 1);
        cs->id->func->cat_str(cs->id, m_xml_get_value(attributes, "id"));
        cs->name->func->cat_str(cs->name, m_xml_get_value(attributes, "name"));
      }

      if(parsing_controller)
      {
        m_controller_skin* cs = controller_skins->func->get_last(controller_skins);
        if(strcmp(name->content, "skin") == 0)
        {
          char* mesh_target = m_xml_get_value(attributes, "source")->content + 1;
          for(unsigned int i = 0; i < geometry_meshs->size; i++)
          {
            m_geometry_mesh* mesh = geometry_meshs->func->get_index(geometry_meshs, i);
            if(strcmp(mesh->id->content, mesh_target) == 0)
            {
              cs->func->set_mesh(cs, mesh);
              break;
            }
          }
        }
        else if(strcmp(name->content, "param") == 0)
        {
          char* param_name = m_xml_get_value(attributes, "name")->content;
          if(strcmp(param_name, "TRANSFORM") == 0)
          {
            for(unsigned int i = 0; i < last_float_array->length; i+= 16)
            {
              m_matrix4 mat;
              for(unsigned int j = 0; j < 16; j++)
              {
                mat.m[j] = last_float_array->data[i + j];
              }
              // int invertalbe = 0;
              // mat = matrix4_invert(mat,&invertalbe);
              GENERIC_ARRAY_PUSH(cs->bind_poses, m_matrix4, mat);
            }
          }
          else if(strcmp(param_name, "WEIGHT") == 0)
          {
            for(unsigned int i = 0; i < last_float_array->length; i++)
            {
              GENERIC_ARRAY_PUSH(cs->weights, float, last_float_array->data[i]);
            }
          }
        }
      }

      if(strcmp(name->content, "visual_scene") == 0)
      {
        parsing_visual_scene = 1;
      }
      else if(parsing_visual_scene)
      {
        if(strcmp(name->content, "node") == 0)
        {
          char* type = m_xml_get_value(attributes, "type")->content;
          if(strcmp(type, "JOINT") == 0)
          {
            start_join = 1;
            m_visual_scene_join* join = m_visual_scene_join_new();
            // m_skin_join* join = m_skin_join_new();
            join->id->func->cat_str(join->id, m_xml_get_value(attributes, "id"));
            join->name->func->cat_str(join->name, m_xml_get_value(attributes, "name"));
            join->sid->func->cat_str(join->sid, m_xml_get_value(attributes, "sid"));

            if( ! current_join)
            {
              current_join = join;
              if(current_node)
              {
                current_join->transform = current_node->transform;
              }
            }
            else
            {
              current_join->func->add_child(current_join, join);
              current_join = join;
            }
          }
          else if(strcmp(type, "NODE") == 0)
          {
            m_visual_scene_node* vsn = m_visual_scene_node_new();
            vsn->id->func->cat_str(vsn->id, m_xml_get_value(attributes, "id"));
            vsn->name->func->cat_str(vsn->name, m_xml_get_value(attributes, "name"));
            if(is_node)
            {
              current_node->func->add_child(current_node, vsn);
            }
            current_node = vsn;
          }
        }
        else if(strcmp(name->content, "instance_controller") == 0)
        {
          char* url = m_xml_get_value(attributes, "url")->content + 1;
          current_node->func->set_skin_url(current_node, new_string_from_char(url));
          is_node = 1;
        }
        else if(strcmp(name->content, "instance_geometry") == 0)
        {
          char* url = m_xml_get_value(attributes, "url")->content + 1;
          current_node->func->set_geometry_url(current_node, new_string_from_char(url));
          is_node = 1;
        }
      }

    },0),

    SAFE_NEW_LAMBDA(void, (int depth, m_string* name, m_string* content)
    {
      if(parsing_geometry_mesh)
      {
        m_geometry_mesh* gm = geometry_meshs->func->get_last(geometry_meshs);
        if(strcmp(name->content, "float_array") == 0)
        {
          m_mesh_source* source = gm->sources->func->get_last(gm->sources);
          char* ch;
          char s[4] = " \t\n";
          ch = strtok(content->content, s);
          while(ch != NULL)
          {
            float f;
            sscanf(ch, "%f", &f);
            source->farr->func->push(source->farr, f);
            ch = strtok(NULL, s);
          }
        }

        if(parsing_polylist)
        {
          m_mesh_polylist* polylist = gm->polylist;
          if(strcmp(name->content, "vcount") == 0)
          {
            char* ch;
            char s[4] = " \t\n";
            ch = strtok(content->content, s);
            while(ch != NULL)
            {
              int d;
              sscanf(ch, "%d", &d);
              polylist->vcount->func->push(polylist->vcount, d);
              ch = strtok(NULL, s);
            }
          }
          else if(strcmp(name->content, "p") == 0)
          {
            char* ch;
            char s[4] = " \t\n";
            ch = strtok(content->content, s);
            int add = -1;
            while(ch != NULL)
            {
              int d;
              sscanf(ch, "%d", &d);
              polylist->p->func->push(polylist->p, d);
              ch = strtok(NULL, s);
            }
          }
        }
      }
      else if(parsing_controller)
      {
        m_controller_skin* cs = controller_skins->func->get_last(controller_skins);
        if(strcmp(name->content, "bind_shape_matrix") == 0)
        {
          char* ch;
          char s[4] = " \t\n";
          ch = strtok(content->content, s);
          int index = 0;
          while(ch != NULL)
          {
            float f;
            sscanf(ch, "%f", &f);
            cs->bind_shape_matrix.m[index] = f;
            index++;
            ch = strtok(NULL, s);
          }
        }
        else if(strcmp(name->content, "Name_array") == 0)
        {
          char* ch;
          char s[4] = " \t\n";
          ch = strtok(content->content, s);
          while(ch != NULL)
          {
            cs->join_names->func->push(cs->join_names, new_string_from_char(ch), 1);
            ch = strtok(NULL, s);
          }
        }
        else if(strcmp(name->content, "float_array") == 0)
        {
          char* ch;
          char s[4] = " \t\n";
          ch = strtok(content->content, s);
          last_float_array = m_float_array_new();
          while(ch != NULL)
          {
            float f;
            sscanf(ch, "%f", &f);
            last_float_array->func->push(last_float_array, f);
            ch = strtok(NULL, s);
          }
        }
        else if(strcmp(name->content, "vcount") == 0)
        {
          char* ch;
          char s[4] = " \t\n";
          ch = strtok(content->content, s);
          while(ch != NULL)
          {
            int f;
            sscanf(ch, "%d", &f);
            GENERIC_ARRAY_PUSH(cs->vcount, int, f);
            cs->max_vcount = MAX(cs->max_vcount, f);
            ch = strtok(NULL, s);
          }
        }
        else if(strcmp(name->content, "v") == 0)
        {
          char* ch;
          char s[4] = " \t\n";
          ch = strtok(content->content, s);
          while(ch != NULL)
          {
            int f;
            sscanf(ch, "%d", &f);
            GENERIC_ARRAY_PUSH(cs->v, int, f);
            ch = strtok(NULL, s);
          }
        }
      }
      else if(parsing_visual_scene)
      {
        if(start_join)
        {
          if(strcmp(name->content, "matrix") == 0)
          {
            char s[4] = " \t\n";
            char* ch = strtok(content->content, s);
            int index = 0;
            float f;
            m_matrix4 temp;
            while(ch != NULL)
            {
              sscanf(ch, "%f", &f);
              temp.m[index] = f;
              index++;
              ch = strtok(NULL, s);
            }
            if(current_join->parent)
            {
              current_join->transform = temp;
            }
            else
            {
              current_join->transform = matrix4_mul(current_join->transform, temp);
            }
          }
        }

        if(!is_node)
        {
          // if(strcmp(name->content, "roll") == 0)
          // {
          //   float roll;
          //   sscanf(content->content, "%f", &roll);
          //   m_matrix4 temp = matrix4_create_y_rotation(roll);
          //   current_join->transform = matrix4_mul(current_join->transform, temp);
          // }
          // else if(strcmp(name->content, "tip_x") == 0)
          // {
          //   float t;
          //   sscanf(content->content, "%f", &t);
          //   m_matrix4 temp = matrix4_create_translation(t, 0, 0);
          //   current_join->transform = matrix4_mul(current_join->transform, temp);
          // }
          // else if(strcmp(name->content, "tip_y") == 0)
          // {
          //   float t;
          //   sscanf(content->content, "%f", &t);
          //   m_matrix4 temp = matrix4_create_translation(0, 0, t);
          //   current_join->transform = matrix4_mul(current_join->transform, temp);
          // }
          // else
          // if(strcmp(name->content, "tip_z") == 0)
          // {
          //   float t;
          //   sscanf(content->content, "%f", &t);
          //   m_matrix4 temp = matrix4_create_z_rotation(t);
          //   current_join->transform = matrix4_mul(current_join->transform, temp);
          // }
        }

        if(is_node)
        {
          if(strcmp(name->content, "matrix") == 0)
          {
            char s[4] = " \t\n";
            char* ch = strtok(content->content, s);
            int index = 0;
            float f;
            while(ch != NULL)
            {
              sscanf(ch, "%f", &f);
              current_node->transform.m[index] = f;
              index++;
              ch = strtok(NULL, s);
            }
          }
          if(strcmp(name->content, "skeleton") == 0)
          {
            current_node->func->set_skeleton(current_node, current_join);
          }
        }
        else
        {
          if(current_node && strcmp(name->content, "matrix") == 0)
          {
            char s[4] = " \t\n";
            char* ch = strtok(content->content, s);
            int index = 0;
            float f;
            while(ch != NULL)
            {
              sscanf(ch, "%f", &f);
              current_node->transform.m[index] = f;
              index++;
              ch = strtok(NULL, s);
            }
          }
        }
      }
    },0),

    SAFE_NEW_LAMBDA(void, (int depth, m_string* name)
    {
      if(parsing_geometry_mesh)
      {
        if(strcmp(name->content, "vertices") == 0)
        {
          parsing_vertices = 0;
        }
        if(strcmp(name->content, "polylist") == 0)
        {
          parsing_polylist = 0;
        }
        if(strcmp(name->content, "geometry") == 0)
        {
          parsing_geometry_mesh = 0;
        }
      }

      if(parsing_controller)
      {
        if(strcmp(name->content, "controller") == 0)
        {
          parsing_controller = 0;
        }
      }

      if(parsing_visual_scene)
      {
        if(strcmp(name->content, "visual_scene") == 0)
        {
          parsing_visual_scene = 0;
        }
        else if(strcmp(name->content, "node") == 0)
        {
          if(start_join)
          {
            if(current_join->parent)
            {
              current_join = current_join->parent->owner;
            }
            else
            {
              // reach root
              start_join = 0;
            }
          }
          if(is_node)
          {
            if(current_node->parent)
            {
              current_node = current_node->parent->owner;
            }
            else
            {
              visual_nodes->func->push(visual_nodes, current_node, 1);
              current_node = 0;
              is_node = 0;
            }
          }
        }
      }
    },0)

  );

  /********************************************
  *           generate node
  *********************************************/
  m_list* node_results = array_list_new();
  m_skin_node* current_node_parent = 0;
  m_list* node_parse_stack = linked_list_new();
  m_list* visual_join_keys = array_list_new();
  m_list* joins_created = array_list_new();

  for(long i = visual_nodes->size - 1; i >= 0; i--)
  {
    _(node_parse_stack, insert, _(visual_nodes, get_index, i), 0, 1);
  }

  while(node_parse_stack->size)
  {
    m_visual_scene_node* vsn = _(node_parse_stack, get_first);
    _(node_parse_stack, remove_index, 0);
    m_skin_node* new_node = m_skin_node_new();
    _(node_results, push, new_node, 1);
    if(current_node_parent)
    {
      _(current_node_parent, add_child, new_node);
      current_node_parent = new_node;
    }
    else
    {
      current_node_parent = new_node;
    }
    if(vsn->skeleton)
    {
      int found = 0;
      for(long j = 0; j < visual_join_keys->size; j++)
      {
        m_visual_scene_join* v = _(visual_join_keys, get_index, j);
        if(v == vsn->skeleton)
        {
          _(new_node, set_join, _(joins_created, get_index, j));
          found = 1;
          break;
        }
      }

      if(!found)
      {
        lambda_ref* create_skin_join = SAFE_NEW_LAMBDA(m_skin_join*,(m_visual_scene_join* join)
        {
          for(long j = 0; j < controller_skins->size; j++)
          {
            m_controller_skin* cs = _(controller_skins, get_index, j);
            for(long k = 0; k < cs->join_names->size; k++)
            {
              m_string* join_name = _(cs->join_names, get_index, k);
              if(strcmp(join_name->content, join->sid->content) == 0)
              {
                m_skin_join* ret = m_skin_join_new();
                _(ret->id, cat_str, join->id);
                _(ret->name, cat_str, join->name);
                _(ret->sid, cat_str, join->sid);
                _(ret->uniform_id, cat_char, "joins[");
                char id[10];
                snprintf(id, sizeof(id), "%d", k);
                _(ret->uniform_id, cat_char, id);
                _(ret->uniform_id, cat_char, "]");
                ret->transform = join->transform;
                // {
                //   quaternion offset_q = quaternion_new_angle_axis(DEG_TO_RAD(90), 1, 0, 0);
                //   m_matrix4 m = matrix4_create_quaternion(offset_q);
                //   ret->transform = matrix4_mul(ret->transform, m);
                // }
                // ret->bind_pose = GENERIC_ARRAY_GET(cs->bind_poses, m_matrix4, k);
                //
                // int invertable = 0;
                // ret->inverse_bind_pose = matrix4_invert(ret->bind_pose, &invertable);
                ret->inverse_bind_pose = GENERIC_ARRAY_GET(cs->bind_poses, m_matrix4, k);
                return ret;
              }
            }
          }
          return (m_skin_join*)0;
        }, 0);
        // create m_skin_join tree
        m_list* queue = linked_list_new();
        _(queue, push, vsn->skeleton, 1);
        m_skin_join* parent = 0;
        m_skin_join* join_root = 0;
        while(queue->size)
        {
          m_visual_scene_join* msj = _(queue, get_first);
          _(queue, remove_index, 0);

          m_skin_join* join = create_skin_join->callback(msj);
          if(!join_root) join_root = join;
          if(parent)
          {
            _(parent, add_child, join);

            m_skin_join* join_parent = join->parent->owner;
            m_matrix4 temp = join->inverse_bind_pose;
            while(join_parent)
            {
              temp = matrix4_mul(join_parent->inverse_bind_pose, temp);
              if(join_parent->parent) join_parent = join_parent->parent->owner;
              else break;
            }
            int invertable = 0;
            join->bind_pose = matrix4_invert(temp, &invertable);

          }
          else
          {
            int invertable = 0;
            join->bind_pose = matrix4_invert(join->inverse_bind_pose, &invertable);

          }
          parent = join;

          if(msj->children->size)
          {
            for(long j = msj->children->size - 1; j >= 0; j--)
            {
             _(queue, insert, _(msj->children, get_index, j), 0, 1);
            }
          }
          else
          {
            if(parent->parent) parent = parent->parent->owner;
          }
        }

        _(new_node, set_join, join_root);
        _(visual_join_keys, push, vsn->skeleton, 1);
        _(joins_created, push, join_root, 1);
      }

      //find skin
      m_controller_skin* node_skin = 0;
      for(long i = 0; i < controller_skins->size; i++)
      {
        m_controller_skin* skin = _(controller_skins, get_index, i);
        if(strcmp(skin->id->content, vsn->url->content) == 0)
        {
          node_skin = skin;
          break;
        }
      }
      _(new_node, build_skin, node_skin);
    }
    else if(vsn->children->size)
    {
      for(long j = 0; j < geometry_meshs->size; j++)
      {
        m_geometry_mesh* gm = _(geometry_meshs, get_index, j);
        if(strcmp(vsn->geometry_url->content, gm->id->content) == 0)
        {
          _(new_node, build_mesh, gm);
          break;
        }
      }
    }

    if(vsn->children->size)
    {
      for(long j = vsn->children->size - 1; j >= 0; j--)
      {
        _(node_parse_stack, insert, _(vsn->children, get_index, j), 0, 1);
      }
    }
    else
    {
      if(current_node_parent->parent) current_node_parent = current_node_parent->parent->owner;
    }
  }

  QUICK_RELEASE(geometry_meshs);
  QUICK_RELEASE(controller_skins);
  QUICK_RELEASE(visual_nodes);
  return node_results;
}

#ifdef __cplusplus
}
#endif
