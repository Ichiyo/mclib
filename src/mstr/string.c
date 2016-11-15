#include "mstr/string.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

static void free_string(m_string* arg)
{
	free(arg->content);
	free(arg);
}

static void mstr_mstr(m_string* des, m_string* src)
{
	des->content = realloc(des->content, (des->length + src->length + 1) * sizeof(char));
	memcpy(des->content + des->length, src->content, src->length);
	des->length = des->length + src->length;
	des->content[des->length] = '\0';
}

static void mstr_char(m_string* des, char* src)
{
	unsigned long src_size = strlen(src);
	des->content = realloc(des->content, (des->length + src_size + 1) * sizeof(char));
	strncpy(des->content + des->length, src, src_size);
	des->length = des->length + src_size;
	des->content[des->length] = '\0';
}

static void mstr_replace_string(m_string* str, m_string* before, m_string* after)
{
	m_string* temp = new_string();

	int start = -1;
	int end = -2;
	int count = 0;
	int first_between = -1;
	for(int i = 0; i < str->length; i++)
	{
		if(str->content[i] == before->content[count])
		{
			if(first_between == -1 && count > 0 && str->content[i] == before->content[0])
			{
				first_between = i;
			}

			count++;
			if(count == before->length)
			{
				if(end >= start)
				{
					//copy str[start,end] to temp
					int size = end - start + 1;
					temp->content = realloc(temp->content, (temp->length + size + 1) * sizeof(char));
					strncpy(temp->content + temp->length, str->content + start, size);
					temp->length = temp->length + size;
					temp->content[temp->length] = '\0';
				}
				// copy after to temp
				mstr_mstr(temp, after);
				first_between = -1;
				start = i+1;
				end = i;
				count = 0;
			}
			else if(i == str->length - 1)
			{
				end = i;
				if(start < 0) start = 0;
			}
		}
		else
		{
			if(start < 0) start = 0;

			count = 0;
			if(first_between > 0)
			{
				i = first_between;
				first_between = -1;
				count++;
				end = i - 1;
			}
			else
			{
				if(str->content[i] == before->content[count])
				{
					end = i - 1;
					count++;
				}
				else
				{
					end = i;
				}
			}

			if(i == str->length - 1) end = i;
		}
	}
	if(end >= start)
	{
		int size = end - start + 1;
		temp->content = realloc(temp->content, (temp->length + size + 1) * sizeof(char));
		strncpy(temp->content + temp->length, str->content + start, size);
		temp->length = temp->length + size;
		temp->content[temp->length] = '\0';
	}

	str->length = 0;
	free(str->content);
	str->content = 0;
	mstr_mstr(str, temp);
	temp->func->release(temp);
}

static void mstr_to_uppercase(m_string* str)
{
	int i = 0;
	while(str->content[i])
	{
		str->content[i] = toupper(str->content[i]);
		i++;
	}
}

static void mstr_to_lowercase(m_string* str)
{
	int i = 0;
	while(str->content[i])
	{
		str->content[i] = tolower(str->content[i]);
		i++;
	}
}

static void mstr_clear(m_string* str)
{
	str->length = 0;
	if(str->content) free(str->content);
	str->content = 0;
}

static void mstr_insert_after(m_string* str, m_string* stencil, m_string* in)
{
	//dirty implementation , need improvement
	m_string* buff = new_string_from_str(stencil);
	buff->func->cat_str(buff, in);
	mstr_replace_string(str, stencil, buff);
	buff->func->release(buff);
}

static int mstr_contain_char(m_string* str, char* in)
{
	int in_length = strlen(in);

	int count = 0;
	int first_between = -1;
	for(int i = 0; i < str->length; i++)
	{
		if(str->content[i] == in[count])
		{
			if(first_between == -1 && count > 0 && str->content[i] == in[0])
			{
				first_between = i;
			}
			count++;
			if(count == in_length)
			{
				return 1;
			}
		}
		else
		{
			if(i == str->length - 1) break;

			count = 0;
			if(first_between > 0)
			{
				i = first_between;
				first_between = -1;
				count++;
			}
			else
			{
				if(str->content[i] == in[count])
				{
					first_between = -1;
					count++;
				}
			}
		}
	}
	return 0;
}

static int mstr_contain_str(m_string* str, m_string* in)
{
	int count = 0;
	int first_between = -1;
	for(int i = 0; i < str->length; i++)
	{
		if(str->content[i] == in->content[count])
		{
			if(first_between == -1 && count > 0 && str->content[i] == in->content[0])
			{
				first_between = i;
			}
			count++;
			if(count == in->length)
			{
				return 1;
			}
		}
		else
		{
			if(i == str->length - 1) break;

			count = 0;
			if(first_between > 0)
			{
				i = first_between;
				first_between = -1;
				count++;
			}
			else
			{
				if(str->content[i] == in->content[count])
				{
					count++;
				}
			}
		}
	}

	return 0;
}

static int mstr_equal_char(m_string* str, char* c)
{
	return strcmp(str->content, c) == 0;
}

static int mstr_equal_str(m_string* str, m_string* in)
{
	return strcmp(str->content, in->content) == 0;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

static m_string_func base_m_string_func =
{
	BASE_REF_FUNC_INHERIT,
	.free = free_string,
	.cat_str = mstr_mstr,
	.cat_char = mstr_char,
	.replace_str = mstr_replace_string,
	.to_uppercase = mstr_to_uppercase,
	.to_lowercase = mstr_to_lowercase,
	.clear = mstr_clear,
	.insert_after = mstr_insert_after,
	.contain_str = mstr_contain_str,
	.contain_char = mstr_contain_char,
	.equal_char = mstr_equal_char,
	.equal_str = mstr_equal_str
};

m_string* new_string()
{
	REF_NEW_AUTO_RELEASE(m_string, str)
	mstr_char(str, "");
	str->func = &base_m_string_func;
	return str;
}

m_string* new_string_from_char(char* in)
{
	m_string* ret = new_string();
	mstr_char(ret, in);
	return ret;
}

m_string* new_string_from_str(m_string* in)
{
	m_string* ret = new_string();
	mstr_mstr(ret, in);
	return ret;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
