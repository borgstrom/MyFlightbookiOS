# Getting Started
See the license agreement for the code.  My one additional rule is "no laughing."  You will see lots of remnants from where I was building my first "Hello World" iOS app, from which this evolved.  Heck, it's still called "MFBSample" because I didn't originally intend for it to become the actual codebase...it just kinda grew.

Anyhow...
## 1. Create an ApiKeys file
You'll need to create an "ApiKeyS.h" file with the following structure:
~~~~
#ifndef ApiKeys_h
#define ApiKeys_h

NSString * const _szKeyAppToken = @"[api key for web service goes here]";

#endif /* ApiKeys_h */
~~~~
The actual value for the web service key is the token that you use to identify this app as being authorized to make web service calls.

## 2 Debugging
Most everything in the project includes MFBAppDelegate.h.  This defines "MFBHOSTNAME", which is the DNS name of the web service.  In retail, this is MyFlightbook.com, but for debugging you may wish to point to a private test server.  

There is a #ifdef DEBUG surrounding an alternative DNS name; set this to whatever test environment you are using.  Note that the structure must still be https://{MFBHOSTNAME}/logbook/{rest of URL}.

I *STRONGLY* recommend creating an additional scheme to test retail vs. debug mode.  There are a few differences in functionality between the two modes:
* The aforementioend MFBHOSTNAME determines which server you will hit.  PLEASE DO NOT USE THE LIVE SITE if you will be changing any data.  I can point you to a test server.  
* Most significant functional difference: if DEBUG is defined, starting the engine will simulate a series of GPS events.
* Some logging only occurs when DEBUG is allowed
* You can only use HTTP with a 192.* address (i.e., local); otherwise, must be HTTPS

Note that you can tell which server you are using by going to the Profile tab, tapping "About MyFlightbook", and then scrolling to the bottom; it will show you the following information:
[MFBHostname] [Takeoff Speed] [Landing Speed] [Version]
E.g., "MyFlightbook.com 70 55 3.0.1"

## 3 Using Soap
MyFlightbook uses SOAP (no snickering) to make it's web service calls.  You can find the current WSDL [here](http://myflightbook.com/logbook/public/webservice.asmx?WSDL).  

All of the code to consume the webservice is autogenerated using a tool called WSDLToObjC.  It's a MacOS app that consumes a .wsdl file and spits out a bunch of objective-c files upon which the rest of the code depends.  WSDLToObjC was originally an open source project of its own but became orphaned.  I have resurrected it [here](https://github.com/ericberman/WSDLtoObjC). 

I have preserved the original MIT license for it.

