xml读

```c
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <iostream>
#include <string>

typedef struct{
        char *DevType;
        char *DeviceWANComm[6];
        char *DeviceRAW[6];
        char *DeviceSerial[5];
        char *DeviceUISendComm[7];
        char *DeviceUIRecvComm[6];
        char *DeviceMSTun[8];
}device;

int read(xmlDocPtr doc, xmlNodePtr cur, device &ret);
int readToChar(xmlDocPtr doc, xmlNodePtr cur, char* front, char *value);

int readXml(const char* docName, device & ret)
{
        xmlKeepBlanksDefault(0) ;
        xmlIndentTreeOutput = 1 ;
        xmlDocPtr doc= NULL;
        doc = xmlParseFile(docName);
        if(NULL == doc)
        {
                std::cout<<"failed to parse the file"<<std::endl;
                return 1;
        }

        xmlNodePtr cur = NULL;
        cur = xmlDocGetRootElement(doc);

        if(NULL == cur)
        {
                std::cout<<"it is an empty document"<<std::endl;
                xmlFreeDoc(doc);
                return 2;
        }
        read(doc, cur,  ret);
        printf("*********write over*********\n");
}

int read(xmlDocPtr doc, xmlNodePtr cur, device & ret)
{
        int record = 0;

        cur = cur->xmlChildrenNode;
        char *content =(char *) xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
        record++;
        ret.DevType = content;

        cur = cur->next;
        xmlNodePtr curChild = cur->xmlChildrenNode;
        int i = 0;
        for(i = 0; i < 6; i++)
        {
                content =(char *) xmlNodeListGetString(doc, curChild->xmlChildrenNode, 1);
                ret.DeviceWANComm[i] = content;
                curChild = curChild->next;
                record++;
        }

        cur = cur->next;
        curChild = cur->xmlChildrenNode;
        for(i = 0; i < 6; i++)
        {
                content =(char *) xmlNodeListGetString(doc, curChild->xmlChildrenNode, 1);
                ret.DeviceRAW[i] = content;
                curChild = curChild->next;
                record++;
        }

            cur = cur->next;
        curChild = cur->xmlChildrenNode;
        for(i = 0; i < 5; i++)
        {
                content =(char *) xmlNodeListGetString(doc, curChild->xmlChildrenNode, 1);
                ret.DeviceSerial[i] = content;
                curChild = curChild->next;
                record++;
        }

        cur = cur->next;
        curChild = cur->xmlChildrenNode;
        for(i = 0; i < 6; i++)
        {
                content =(char *) xmlNodeListGetString(doc, curChild->xmlChildrenNode, 1);
                ret.DeviceUISendComm[i] = content;
                curChild = curChild->next;
                record++;
        }

        cur = cur->next;
        curChild = cur->xmlChildrenNode;
        for(i = 0; i < 6; i++)
        {
                content =(char *) xmlNodeListGetString(doc, curChild->xmlChildrenNode, 1);
                ret.DeviceUIRecvComm[i] = content;
                curChild = curChild->next;
                printf("!!!!!!!!!!!!%s\n\n",ret.DeviceUIRecvComm[i]);
                record++;
        }

        cur = cur->next;
        curChild = cur->xmlChildrenNode;
        for(i = 0; i < 8; i++)
        {
                content =(char *) xmlNodeListGetString(doc, curChild->xmlChildrenNode, 1);
                ret.DeviceMSTun[i] = content;
                curChild = curChild->next;
                record++;
        }

        xmlFree(curChild);
        free(content);
        return record;

}

void showDevice(device &obj)
{
        printf("DeviceWANComm%s\n", obj.DevType);
        int i = 0;
        for( i = 0; i < 6; i++)printf("%s\n",obj.DeviceWANComm[i]);
        printf("\nDeviceRAW\n");
        for( i = 0; i < 6; i++)printf("%s\n",obj.DeviceRAW[i]);
        printf("\nDeviceSerial\n");
        for( i = 0; i < 5; i++)printf("%s\n",obj.DeviceSerial[i]);
        printf("\nDeviceUISendComm\n");
        for( i = 0; i < 6; i++)printf("%s\n",obj.DeviceUISendComm[i]);
        printf("\nDeviceUIRecvComm\n");
        for( i = 0; i < 6; i++)printf("%s\n",obj.DeviceUIRecvComm[i]);
        printf("\nDeviceMSTun\n");
        for( i = 0; i < 8; i++)printf("%s\n",obj.DeviceMSTun[i]);
        printf("\n**************end***********\n");
}

int main()
{
        device ret = {0};
        readXml("test.xml", ret);
        showDevice(ret);
        return 0;
}
  
```



结果

```c
*********write over*********
DeviceWANCommmaster
1000
WANComm
11.0.0.0
5000
10.10.0.219
8000

DeviceRAW
2000
Serial-Master
eth1
 IP 
 L2  
    ETH_P_ALL   

DeviceSerial
3000
Serial-0
/dev/ttyACM0
 Point2Point 
115200   

DeviceUISendComm
4000
UIComm
11.0.0.0
1025
192.168.254.10
32771

DeviceUIRecvComm
4010
UIRecvComm
11.0.0.0
1024
192.168.254.10
32771

DeviceMSTun
5000
MSTun
 Point2Point 
192.168.8.8
192.168.8.9
255.255.255.0
  1400       


**************end***********

```



​	写

```c
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <iostream>

void write(xmlDocPtr doc, xmlNodePtr cur, const xmlChar* limit, const xmlChar* des, const xmlChar *after);
void write(xmlDocPtr doc, xmlNodePtr cur, const xmlChar* des, const xmlChar *after);
int  writeXml(const char *docName,const char* limit, const char *des, const char *after);

int  writeXml(const char *docName,const char *des, const char *after)
{
        writeXml(docName, NULL, des, after);
        return 0;
}

int  writeXml(const char *docName,const char *limit,const char *des, const char *after)
{
        xmlKeepBlanksDefault(0) ;
        xmlIndentTreeOutput = 1 ;
        xmlDocPtr doc= NULL;
        doc = xmlParseFile(docName);
        if(NULL == doc)
        {
                std::cout<<"failed to parse the file"<<std::endl;
                return 1;
        }

        xmlNodePtr cur = NULL;
        cur = xmlDocGetRootElement(doc);

        if(NULL == cur)
        {
                std::cout<<"it is an empty document"<<std::endl;
                xmlFreeDoc(doc);
                return 2;
        }

        if(limit != NULL)
        {

                write(doc, cur, (const xmlChar *)limit, (const xmlChar *)des, (const xmlChar *)after);
        }else
        {

                write(doc, cur, (const xmlChar *)des, (const xmlChar *)after);
        }

        xmlFree(cur);
        cur = xmlDocGetRootElement(doc);

        if(NULL == cur)
        {
                std::cout<<"it is an empty document"<<std::endl;
                xmlFreeDoc(doc);
                return 2;
        }

        if(limit != NULL)
        {

                write(doc, cur, (const xmlChar *)limit, (const xmlChar *)des, (const xmlChar *)after);
        }else
        {

                write(doc, cur, (const xmlChar *)des, (const xmlChar *)after);
        }

        xmlFree(cur);
        xmlSaveFormatFile ("test.xml", doc, 1);

        xmlFreeDoc(doc);

        return 0;
}

void write(xmlDocPtr doc, xmlNodePtr cur, const xmlChar *des, const xmlChar* after)
{
        if(NULL == cur->xmlChildrenNode)
        {

                xmlNodePtr temp = cur->next;
                if(NULL != temp)
                {
                        xmlChar *xxx = xmlNodeListGetString(doc, temp, 1);
                        printf("%s\n", xxx);
                        write(doc, temp, des, after);
                        xmlFree(temp);
                        return;
                }
                return;
        }

        if(false == xmlStrcmp(cur->name, des))
        {
                xmlChar *xxx = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

                xmlNodeSetContent(cur, after);

                std::cout<<cur->name<<" "<<cur->name<<": "<<xxx;
                xxx = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                std::cout<<"   then: "<<xxx<<std::endl;

                if(NULL != xxx)
                {
                        xmlFree(xxx);
                }
        }


        xmlNodePtr temp = cur->xmlChildrenNode;
        write(doc, temp, des, after);

        temp = cur->next;
        if(NULL != temp)
        {
                write(doc,temp, des, after);
                xmlFree(temp);
        }
}
void write(xmlDocPtr doc, xmlNodePtr cur ,const xmlChar* limit, const xmlChar* des, const xmlChar *after)
{
        if(NULL == cur->xmlChildrenNode)
        {
                xmlNodePtr temp = cur->next;
                if(NULL != temp)
                {
                        write(doc, temp, limit, des, after);
                        xmlFree(temp);
                        return;
                }
                xmlFree(temp);
                return;
        }

        if(false == xmlStrcmp(cur->name, limit))
        {
                xmlNodePtr tempNode = cur->xmlChildrenNode;
                while(tempNode != NULL)
                {
                        if((false == xmlStrcmp(tempNode->name, des)))
                        {
                                xmlChar *xxx = xmlNodeListGetString(doc, tempNode->xmlChildrenNode, 1);

                                xmlNodeSetContent(tempNode, after);

                                std::cout<<cur->name<<" "<<tempNode->name<<": "<<xxx;
                                xxx = xmlNodeListGetString(doc, tempNode->xmlChildrenNode, 1);
                                std::cout<<"   then: "<<xxx<<std::endl;

                                if(NULL != xxx)
                                {
                                        xmlFree(xxx);
                                }
                                return;
                        }
                        tempNode = tempNode->next;
                }
                return;
        }

        xmlNodePtr temp = cur->xmlChildrenNode;
        write(doc,temp, limit, des, after);
        temp = cur->next;
        if(NULL != temp)
        {
                write(doc, temp, limit, des, after);
                xmlFree(temp);
        }
}

int main()
{
        //writeXml("test.xml", "DeviceWANComm", "LocalIP", "11.0.0.0");
        writeXml("test.xml", "LocalIP", "11.0.0.0");
        std::cout<<"******************end write******************"<<std::endl;
        return 0;
}

                                                                                                                                                                                                                        

```

