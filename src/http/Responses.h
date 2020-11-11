//
// Created by Eoin on 27/10/2020.
//

#ifndef SERVERTEST_RESPONSES_H
#define SERVERTEST_RESPONSES_H

struct Response;

//400 series responses
static void generate400Response(Response*&);
static void generate401Response(Response*&);
static void generate403Response(Response*&);
static void generate404Response(Response*&);
static void generate405Response(Response*&);
//500 series responses
static void generate500Response(Response*&);
static void generate501Response(Response*&);

//Helper functions for crafting responses
static const char* getCurTime();

#endif //SERVERTEST_RESPONSES_H
