#include <stdio.h>
#include <string.h>
#include <ts/ts.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <sys/socket.h>
#define PLUGIN_NAME "logapi"
 
static TSTextLogObject logcs = NULL;

static void
request_do(TSHttpTxn txnp)
{
    struct sockaddr const* myaddr = TSHttpTxnClientAddrGet(txnp);
    
    
    struct sockaddr_in ip_addr;
    memcpy(&ip_addr, myaddr, sizeof(ip_addr));
    char* myip = inet_ntoa(ip_addr.sin_addr);
     
    TSTextLogObjectWrite(logcs, "The Client ip %s",myip);
   
  TSHttpTxnReenable(txnp, TS_EVENT_HTTP_CONTINUE);
}
 
static int
request_do_plugin(TSCont contp , TSEvent event, void *edata)
{
  TSHttpTxn txnp = (TSHttpTxn) edata;
 
  switch (event) {
  case TS_EVENT_HTTP_SEND_REQUEST_HDR:
    request_do(txnp);
    return 0;
  default:
    break;
  }
  return 0;
}
 
void TSPluginInit (int argc, const char *argv[])
 
{
  TSPluginRegistrationInfo info;
 
  info.plugin_name = "logapi";
  info.vendor_name = "logapi";
  info.support_email = "b13621367396@gmail.com";
  
TSTextLogObjectCreate(PLUGIN_NAME, TS_LOG_MODE_ADD_TIMESTAMP, &logcs);
 
  if (TSPluginRegister(TS_SDK_VERSION_3_0, &info) != TS_SUCCESS) {
    TSError("Plugin registration failed. \n");
  }
   TSCont cont = TSContCreate(request_do_plugin, NULL);
 
  TSHttpHookAdd(TS_HTTP_SEND_REQUEST_HDR_HOOK,cont);
}
