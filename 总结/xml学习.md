# xml学习

1.文档必须有根元素

2.大小敏感

3.正确嵌套

```c
<b><i><jwkwnf;l3nln3n></i></b>
```

4.属性值加引号

```c
<note date="08/08/2008">
<to>George</to>
<from>John</from>
</note> 
```

5.实体引用

| \&lt;   | <    | 小于   |
| ------- | ---- | ------ |
| \&gt;   | >    | 大于   |
| \&amp;  | &    | 和号   |
| \&apos; | '    | 单引号 |
| \&quot; | "    | 引号   |

**<**和**&**非法，必须使用实体引用

6.注释

<--! it is a comment. -->

7.多个空格合并为一个

解析xml：

```
<?xml version="1.0"?>
<story>
  <storyinfo>
    <author>John Fleck</author>
    <datewritten>June 2,2002</datewritten>
    <keyword>example keyword</keyword>
  </storyinfo>
  <body>
    <headline>This is the headline</headline>
    <para>This is the body text.</para>
  </body>
</story>
```

解析story部分字符串：

```c++
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

 void  parseStory (xmlDocPtr doc, xmlNodePtr cur)
  {
          xmlChar *key, *name, *date;
          cur = cur->xmlChildrenNode;
          while (cur != NULL)
          {
                  if ((false == xmlStrcmp(cur->name, (const xmlChar *)"author")))
                  {
                          name = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                          printf("author: %s\n", name);
                          xmlFree(name);
                  }
                  if ((!xmlStrcmp(cur->name, (const xmlChar *)"keyword")))
                  {
                          key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                          printf("keyword: %s\n", key);
                          xmlFree(key);
                  }
                  if((false == xmlStrcmp(cur->name, (const xmlChar*)"datewritten")))
                  {
                          date = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                          printf("datewritten: %s\n", date);
                          xmlFree(date);
                  }
                  cur = cur->next;
          }
          return;
  }

static void  parseDoc(char *docname)
{
        xmlDocPtr doc = NULL;
        xmlNodePtr cur = NULL;
        doc = xmlParseFile(docname);
        if (NULL == doc )
        {
                fprintf(stderr,"Document not parsed successfully. \n");
                return;
        }
        cur = xmlDocGetRootElement(doc);
        if (NULL == cur)
        {
                fprintf(stderr,"empty document\n");
                xmlFreeDoc(doc);
                return;
        }
        if (xmlStrcmp(cur->name, (const xmlChar *) "story"))
        {
                fprintf(stderr,"document of the wrong type, root node != story");
                xmlFreeDoc(doc);
                return;
        }
        cur = cur->xmlChildrenNode;
        while (NULL != cur)
        {
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"storyinfo")))
                {
                        parseStory (doc, cur);
                }
                cur = cur->next;
        }
        xmlFreeDoc(doc);
        return;
}

int  main(int argc, char **argv)
{
        char *docname = "test.xml";
        parseDoc (docname);
        return (0);
}

```

运行结果：

```c
author: John Fleck
datewritten: June 2,2002
keyword: example keyword
```



json

```c
#include <json/json.h>
#include <string>
#include <iostream>
using namespace std;


int main()
{

    Json::Value array;
    Json::Value root;
    Json::Value person;

    Json::FastWriter writer;


    person["name"] = "allen";
    person["age"] = 10;
    person["sex"] = "male";
    root.append(person);

    person["name"] = "keiv";
    person["age"] = 20;
    person["sex"] = "female";
    root.append(person);

    person["name"] = "lihua";
    person["age"] = 10;
    person["sex"] = "female";
    root.append(person);

        //array["array"].append(root);


    array["array"] = Json::Value(root);

    string data = writer.write(array);
    cout<<data<<endl;

    string strValue = array.toStyledString();
    cout<<strValue<<endl;

    Json::Reader reader;
    Json::Value value;

    if (reader.parse(strValue, value))
    {
         for (unsigned int i = 0; i < value["array"].size(); i++)
        {
            string name = value["array"][i]["name"].asString();
            int     age = value["array"][i]["age"].asInt();
            string sex  = value["array"][i]["sex"].asString();

            cout<<name<<" "<<age<<" "<<sex<<endl;
        }
    }

    return 0;
}
```



结果

```
{"array":[{"age":10,"name":"allen","sex":"male"},{"age":20,"name":"keiv","sex":"female"},{"age":10,"name":"lihua","sex":"female"}]}

{
   "array" : [
      {
         "age" : 10,
         "name" : "allen",
         "sex" : "male"
      },
      {
         "age" : 20,
         "name" : "keiv",
         "sex" : "female"
      },
      {
         "age" : 10,
         "name" : "lihua",
         "sex" : "female"
      }
   ]
}

allen 10 male
keiv 20 female
lihua 10 female
```

