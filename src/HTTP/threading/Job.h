//
// Created by Eoin on 20/08/2020.
//

#ifndef SERVERTEST_JOB_H
#define SERVERTEST_JOB_H

#include <future>

class Request;
class Response;

struct Job{
    std::promise<Response> responsePromise;
    Request requestToProcess;
};

#endif //SERVERTEST_JOB_H
