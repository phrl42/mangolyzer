#pragma once
#ifndef __MAIN__
#define __MAIN__

int main()
{

  Entry* entry = new Entry();
  entry->Init();
  delete entry;
  
  return 0;
}

#endif