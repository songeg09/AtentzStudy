#pragma once


#define SINGLETON(type)		private:\
											type();\
											~type();\
										public:\
										static type* GetInstance()\
										{\
											static type s_iThis;\
											return &s_iThis;\
										}