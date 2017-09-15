// Ceres Solver - A fast non-linear least squares minimizer
// Copyright 2015 Google Inc. All rights reserved.
// http://ceres-solver.org/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name of Google Inc. nor the names of its contributors may be
//   used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Author: keir@google.com (Keir Mierle)
//
// A simple example of using the Ceres minimizer.
//
// Minimize 0.5 (10 - x)^2 using jacobian matrix computed using
// automatic differentiation.
#include "ceres/ceres.h"
#include "glog/logging.h"
using namespace std;
// A templated cost functor that implements the residual r = 10 -
// x. The method operator() is templated so that we can then use an
// automatic differentiation wrapper around it to generate its
// derivatives.
class Cost{
public:
    template <typename T> 
    bool operator()(const T* const x, T* r) const{
        r[0] = T(20) - x[0];
        r[1] = T(106) - x[1];
        return true;
    };
};
int main(int argc, char** argv){
    ceres::CostFunction *cost = new ceres::AutoDiffCostFunction<Cost, 2, 2>(new Cost);
    ceres::Problem problem;
    ceres::Solver::Options options;
    ceres::Solver::Summary summary;

    double init_x = -200;
    //double x = init_x;
    double x[2] = {12222, 33323123};
    problem.AddResidualBlock(cost, NULL, x);
    options.minimizer_progress_to_stdout = true;
    ceres::Solve(options, &problem, &summary);
    cout << summary.BriefReport() << endl;
    //cout << x << endl;
    cout << x[0] << endl;
    cout << x[1] << endl;
    return 0;
}
