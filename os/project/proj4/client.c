/*
 * Copyright 2021. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었습니다.
 */
#include <stdio.h>
#include <time.h>
#include "threadpool.h"
#include <unistd.h>
#define NCHAR 256
#define NTASK 32
#define NPOOH 62

char *p[NPOOH] = {
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x2E\x2E\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x57\x24\x24\x24\x24\x24\x75",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x46\x2A\x2A\x2B\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x6F\x57\x24\x24\x24\x65\x75",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x2E\x75\x65\x65\x65\x57\x65\x65\x6F\x2E\x2E\x20\x20\x20\x20\x20\x20\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x65\x57\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x62\x2D\x20\x64\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x57",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2C\x2C\x2C\x2C\x2C\x2C\x2C\x75\x65\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x48\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x7E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3A\x65\x6F\x43\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x43\x22\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x54\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x2A\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x65\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x69\x24\x24\x24\x24\x24\x24\x24\x24\x46\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3F\x66\x22\x21\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x75\x64\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2A\x43\x6F",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x20\x20\x20\x6F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x21\x21\x21\x6D\x2E\x2A\x65\x65\x65\x57\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x66\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x55",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x21\x21\x21\x21\x21\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x20\x54\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2A\x21\x21\x2A\x2E\x6F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x65\x2C\x64\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x3A",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x65\x65\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x43",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x62\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2A\x2A\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x21",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x54\x62\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2A\x75\x4C\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x6F\x2E\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x46\x22\x20\x75\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x65\x6E\x20\x60\x60\x60\x20\x20\x20\x20\x2E\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x42\x2A\x20\x20\x3D\x2A\x22\x3F\x2E\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x57\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x6F\x23\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x52\x3A\x20\x3F\x24\x24\x24\x57\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22\x20\x3A\x21\x69\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x21\x6E\x2E\x3F\x24\x3F\x3F\x3F\x22\x22\x60\x60\x2E\x2E\x2E\x2E\x2E\x2E\x2E\x2C\x60\x60\x60\x60\x60\x60\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x60\x60\x20\x20\x20\x2E\x2E\x2E\x2B\x21\x21\x21",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x2A\x20\x2C\x2B\x3A\x3A\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x2A\x60",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x21\x3F\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x7E\x20\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x7E\x60",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2B\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x20\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x3F\x21\x60",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x27\x20\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x2C\x20\x21\x21\x21\x21",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3A\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x27\x20\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x20\x60\x21\x21\x3A",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x2B\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x7E\x7E\x21\x21\x20\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x20\x21\x21\x21\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3A\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x2E\x60\x3A\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x3A\x3A\x20\x60\x21\x21\x2B",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x7E\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x2E\x7E\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x2E\x60\x21\x21\x3A",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7E\x7E\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x20\x3B\x21\x21\x21\x21\x7E\x60\x20\x2E\x2E\x65\x65\x65\x65\x65\x65\x6F\x2E\x60\x2B\x21\x2E\x21\x21\x21\x21\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3A\x2E\x2E\x20\x20\x20\x20\x60\x2B\x7E\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x21\x20\x3A\x21\x3B\x60\x2E\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x75\x20\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x62\x65\x65\x65\x75\x2E\x2E\x20\x20\x60\x60\x60\x60\x60\x7E\x2B\x7E\x7E\x7E\x7E\x7E\x22\x20\x60\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x24\x62",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x55\x55\x24\x55\x24\x24\x24\x24\x24\x20\x7E\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x24\x24\x6F",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2E\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x7E\x20\x24\x24\x24\x75",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x21\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x38\x24\x24\x24\x24\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x58\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x60\x75\x24\x24\x24\x24\x24\x57",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x21\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x21\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22\x2E\x24\x24\x24\x24\x24\x24\x24\x3A",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x2E\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x66\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x27\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2E",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x21",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x21",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x69\x62\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x62\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22\x6F\x24\x24\x24\x62\x2E\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x65\x2E\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x64\x24\x24\x24\x24\x24\x24\x6F\x2E\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x48\x20\x24\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x57\x2E\x60\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x65\x2E\x20\x22\x3F\x3F\x24\x24\x24\x66\x20\x2E\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x64\x24\x24\x24\x24\x24\x24\x6F\x20\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x65\x65\x65\x65\x65\x65\x24\x24\x24\x24\x24\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x62\x75\x20\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x20\x33\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2A\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x64\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x65\x2E\x20\x22\x3F\x24\x24\x24\x24\x24\x3A\x60\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x38",
"\x20\x20\x20\x20\x20\x20\x20\x65\x24\x24\x65\x2E\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x2B\x20\x20\x22\x3F\x3F\x66\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x63",
"\x20\x20\x20\x20\x20\x20\x24\x24\x24\x24\x24\x24\x24\x6F\x20\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x22\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x60\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x62\x2E",
"\x20\x20\x20\x20\x20\x4D\x24\x24\x24\x24\x24\x24\x24\x24\x55\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x22\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x75",
"\x20\x20\x20\x20\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x75",
"\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x6F",
"\x20\x20\x20\x20\x20\x20\x20\x20\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x3F\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x3F\x3F\x24\x24\x24\x24\x24\x24\x24\x46\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x22\x3F\x33\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x2E\x65\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x27",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x75\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x60\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x24\x46\x22",
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x22\x22\x3F\x3F\x3F\x3F\x3F\x22\x22"
};

/*
 * 어떤 정수 X를 인자로 받아서 NCHAR 갯수 만큼 화면에 출력한다.
 * 출력이 종료되었음을 알리기 위해 마지막에 <X>를 출력한다.
 */
void number(void *param)
{
    int i, num;
    
    num = *(int *)param;
    for (i = 0; i < NCHAR; ++i)
        printf("%d", num);
    printf("<%d>\n", num);
}

/*
 * 아무 것도 안 하는 함수로 대기열에서 자리만 차지하기 위해 사용된다.
 */
void donothing(void *param)
{
    /* do nothing */;
}

/*
 * 디즈니 만화 캐릭터인 곰돌이(푸베어)를 출력하는 함수이다.
 */
void pooh(void *param)
{
    int i;
    
    printf("\n");
    for (i = 0; i < NPOOH; ++i)
        printf("%s\n", p[i]);
}

/*
 * 스레드 풀이 잘 구현되었는지 검증하기 위해 작성된 메인 함수이다.
 */
int main(void)
{
    int i, num[NTASK];
    struct timespec req;
    
    /*
     * 잠자는 시간을 10 msec으로 설정한다.
     */
    req.tv_sec = 0;
    req.tv_nsec = 10000000L;
    /*
     * 스레드 풀을 사용하기 전에 먼저 초기화한다.
     */
    pool_init();
    printf("Thread pool: init() completed.\n");
    /*
     * 스레드 풀이 정상으로 종료되는지 검사한다.
     */
    pool_shutdown();
    printf("Thread pool: shutdown() completed.\n");

    /*
     * 스레드 풀을 다시 가동한다.
     */
    pool_init();
    /*
     * 함수 number()를 스레드를 사용해서 실행하기 위해 NTASK 갯수 만큼 스레드 풀에 요청한다.
     * 스레드 풀의 대기열은 길이가 10개를 넘을 수 없어서 요청을 아무리 빨리 처리해도 받을 수 없는
     * 요청이 발생할 수 있다. 대기열이 차서 요청이 거절되면 오류 메시지를 출력한다.
     */
    for (i = 0; i < NTASK; ++i) {
        num[i] = i;
        if (pool_submit(number, num+i))
            printf("%d: Queue is full.\n", i);
    }
    /*
     * 10 msec 동안 자면서 스레드 풀의 대기열이 비기를 기다린다.
     */
    nanosleep(&req, NULL);
    /*
     * 대기열은 비어 있고, 일하는 스레드가 세 개 있으므로,
     * 아래와 같이 세 개의 작업을 요청하면, 두 개의 작업은 아무 것도 안 하니까
     * 마지막 작업은 아무런 방해 없이 곰돌이 이미지를 화면에 출력하게 된다.
     */
    printf("hello\n");
    pool_submit(donothing, NULL);
    pool_submit(donothing, NULL);
    pool_submit(pooh, NULL);
    /*
     * 곰돌이 모습을 다 보기 위해 10 msec 동안 작업이 종료되도록 기다린다.
     */
    nanosleep(&req, NULL);
    /*
     * 스레드 풀을 종료한다.
     */
    pool_shutdown();
    return 0;
}
