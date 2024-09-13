//ManagedObject.h

#ifndef MANAGEDOBJECT_HEADER_
#define MANAGEDOBJECT_HEADER_
#pragma once


#include <winsock2.h>
#include <Ws2tcpip.h> 
#include <windows.h>

using namespace System;
namespace PvxsCLR {

  template<class T>
  public ref class ManagedObject
  {
  protected:
    T* m_Instance;
  public:
    ManagedObject(T* instance)
      : m_Instance(instance)
    {
    }
    virtual ~ManagedObject()
    {
      if (m_Instance != nullptr)
      {
        delete m_Instance;
      }
    }
    !ManagedObject()
    {
      if (m_Instance != nullptr)
      {
        delete m_Instance;
      }
    }
    T* GetInstance()
    {
      return m_Instance;
    }
  };
}
#endif