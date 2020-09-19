/** @file
  This sample application bases on HelloWorld PCD setting
  to print "UEFI Hello World!" to the UEFI Console.

  Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS ret;

  EFI_TIME time; 
  EFI_TIME_CAPABILITIES cap;
  
  volatile UINT32 *ptr = (volatile UINT32 *)0xfee00000u;

  Print (L"HELLO WORLD\n");

  for (int i=0; i< 1024; i++) {
    Print (L"%p: 0x%X\n", ptr + i, *(ptr+i));
  }
  // 调用runtime GetTime Services方法
  ret = gRT->GetTime(&time, &cap);
  if (ret != EFI_SUCCESS) {
    Print (L"Get Time Failed\n");
    return ret;
  }

  // 当前打印日期
  Print(L"%d-%d-%d %d:%d:%d %d %d %d\n", time.Year, time.Month, time.Day,
    time.Hour, time.Minute, time.Second,
    time.Nanosecond, time.TimeZone, time.Daylight);

  Print(L"R:%d,A:%d,STZ:%d\n", cap.Resolution, cap.Accuracy, cap.SetsToZero);

  // 列出所有image handle,打印出来所有image的信息
  return EFI_SUCCESS;
}
