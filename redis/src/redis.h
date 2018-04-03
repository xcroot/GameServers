#ifndef __REDIS_H__
#define __REDIS_H__

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "hiredis.h"
#include "YMSocketData.h"
#include "Hall.h"
#include "Login.h"
#include "LogicServer.h"

#define ZERO_STR '&'

using namespace ::google::protobuf;
using namespace protocol;
class redis{
public:
	redis();
	~redis();
	static redis *getIns();
	bool initial(std::string redisIp, int redisPort, std::string mypass);
	bool reconnect();
	void release();
	bool set(std::string key, char* value,int len);
	bool set(string key,int value);
	char* get(std::string key,int &len);

	bool Hash(std::string key,Message *msg);//����������Щ�������� �û���Ϣ
	Message *getHash(std::string key,string msgname);

	bool List(std::string key, Message *msg);//typename+id(Ψһ):����Ԫ���б� ����ս����Щ��id�Ƿ���ţ�
	bool List(std::string key, char* value);
	std::vector<Message *> getList(std::string key, string mesname);
	std::vector<Message *> getList(std::string key, string mesname,int beginindex,int endindex);
	vector<char *> getList(string key, vector<int> &lens,int beginindex=0, int endindex=-1);
	bool setList(std::string key,string keyname,string value,Message *msg);
	void sortList(std::string key,string keyname,string value);

	bool isConnect();
	void releaseMessages(vector<Message *>vecs);
	void ZeroChange(char *&data, int sz);
	void ChangeToZero(char *&data, int sz);
private:
	vector<string> PushDataToRedis(std::string key, Message *msg);
	Message *PopDataFromRedis(std::string key, map<string, string>maps);

	
private:
	redisContext* m_pConnect;
	redisReply* m_pReply;
	static redis *m_ins;
	string m_ip;
	int m_port;
	string m_pass;
};

#endif