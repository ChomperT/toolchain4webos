/*
*   PDL
*   Copyright 2010-2011 Hewlett-Packard Development Company, L.P. All rights reserved.
*/

#ifndef __PDL_JS__
#define __PDL_JS__

#ifdef __cplusplus
extern "C" {
#endif

#include "PDL_types.h"

/************************* JS COMMUNICATION *******************************/
/************************* JS COMMUNICATION *******************************/
/************************* JS COMMUNICATION *******************************/

/* Register a callback to be a handler for a JS function. For instance, you could 
* call PDL_RegisterJSHandler("foo", MyFunc). In the JS script, you could
* get the native element in the list and call element.foo(), which would lead to the registered
* function being called. */
PDL_Err PDL_RegisterJSHandler(const char *functionName, PDL_JSHandlerFunc function);

/* Same as PDL_RegisterJSHandler, but instead of the js handler being called immediately,
 * the request will be put in a queue, and an event will be posted to SDL to alert you. You 
 * must call PDL_HandleJSCalls to make the actual handlers get called. This approach
 * ensures the handlers are called in your thread (as opposed to PDL_RegisterJSHandler, which
 * calls them immediately from an internal PDK thread). 
 * The event you get is SDL_USEREVENT, The event's user.code value will be PDL_PENDING_JS.
 */
PDL_Err PDL_RegisterPollingJSHandler(const char *functionName, PDL_JSHandlerFunc function);

/* call this after all JS handlers have been registered. Until this function is
* called, NONE of the handlers will work. After this function is called, you may
* not specify any further handlers. */
PDL_Err PDL_JSRegistrationComplete(void);

/* This will call the handlers for any pending downstream js calls
 * that are in the queue. See PDL_RegisterPollingJSHandler's comments
 * for more information. 
 * Returns the number of calls handled, or -1 if there was an error. 
 */
int PDL_HandleJSCalls(void);

/* some helper functions for the JS parameters */
PDL_bool PDL_IsPoller(PDL_JSParameters *parms); /* returns true if the params are being handled by a polling handler. False if they are being handled immediately.*/
int PDL_GetNumJSParams(PDL_JSParameters *parms); /* returns the number of parameters sent */
const char *PDL_GetJSParamString(PDL_JSParameters *parms, int paramNum); /* no allocations. Just returns an internal pointer. Returns "" on failure */
int PDL_GetJSParamInt(PDL_JSParameters *parms, int paramNum); /* returns 0 on failure */
double PDL_GetJSParamDouble(PDL_JSParameters *parms, int paramNum); /* returns 0.0 on failure */

/* call this function to specify your reply to the JS call. It makes a copy
* of the sent-in string, so you don't have to maintain it. */
PDL_Err PDL_JSReply(PDL_JSParameters *parms, const char *reply);

/* same as a reply, but for an exception. This will cause the JavaScript
* function that is being called to throw a JavaScript exception with the
* reply string  */
PDL_Err PDL_JSException(PDL_JSParameters *parms, const char *reply);

/* call this function to proactively call JS functionality from the native side.
* functionName: the name of the function to be called on the JS side. Register this in your JS
*               app by calling: $('MyPlugin').funcName = this.funcName.bind(this); from within the setup
*               function of whatever class you want to handle the call. Replace "MyPlugin" with the name
*               you gave your plugin, and "funcName" with the function name you want to use when calling
*               from the app. 
* params: An array of const char * at least numParams long, containing the parameters to send along as c-strings
* numParams: The number of parameters to be sent to the function */
PDL_Err PDL_CallJS(const char *functionName, const char **params, int numParams);


#ifdef __cplusplus
}
#endif

#endif 
