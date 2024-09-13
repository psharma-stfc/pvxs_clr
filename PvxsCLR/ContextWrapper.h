// Context.h

#ifndef CONTEXT_HEADER_
#define CONTEXT_HEADER_
#pragma once


#include <winsock2.h>
#include <Ws2tcpip.h> 
#include <windows.h>
#include <sstream>

#include "msclr/marshal_cppstd.h"
#include "pvxs/client.h"

//#include "ManagedObject.h"
//
using namespace System;

namespace PvxsCLR {
	public ref class ContextWrapper {//: public ManagedObject<pvxs::client::Config> {

	private:
		pvxs::client::Context* nativeContext; // Pointer to the native class

	public:
		void Initialise() {
			pvxs::client::Config config = pvxs::client::Config::fromEnv();
			nativeContext = new pvxs::client::Context(config);
		}

		// Wrapper for 'get' method
		String^ Get(String^ pvname) {
			try {
				// Configure client using $EPICS_PVA_*
				auto ctxt(pvxs::client::Context::fromEnv());

				// fetch PV "some:pv:name" and wait up to 5 seconds for a reply.
				// (throws an exception on error, including timeout)
				pvxs::Value reply = ctxt.get("TEST:Model_RBV").exec()->wait(5.0);

				pvxs::Value::Fmt fmt = reply.format().delta();

				// Reply is printed to stdout.
				//std::cout << reply;

				std::ostringstream oss;

				// Assuming pvxs::Value::Fmt can be streamed
				// Adjust based on actual methods or streaming operators available for fmt
				oss << fmt;  // Use the appropriate stream operator or method

				// Convert the std::string to System::String^
				std::string fmtString = oss.str();
				return gcnew String(fmtString.c_str());

				/*std::string nativePvName = msclr::interop::marshal_as<std::string>(pvname);
				auto builder = nativeContext->get(nativePvName);
				auto operation = builder.exec();

					auto result = operation->wait(5.0);*/

					//return "Hey";// result.format().delta();
			}
			catch (const std::exception& ex) {
				throw gcnew Exception(gcnew String(ex.what()));
			}
		}

		// Wrapper for 'get' method
		void Put(String^ pvname, int value) {
			std::string nativePvName = "Hello";//= msclr::interop::marshal_as<std::string>(pvname);
			auto builder = nativeContext->put(nativePvName);
			builder.set("value", &value, pvxs::StoreType::Integer, true);
			auto operation = builder.exec();
			try {
				auto result = operation->wait();
				// Handle the result here
			}
			catch (const std::exception& ex) {
				throw gcnew Exception(gcnew String(ex.what()));
			}
		}

	};
}
#endif