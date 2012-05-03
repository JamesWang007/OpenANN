#include "CMAESTestCase.h"
#include <optimization/IPOPCMAES.h>
#include "optimization/Rosenbrock.h"
#include "optimization/Himmelblau.h"
#include "optimization/Ellinum.h"

void CMAESTestCase::run()
{
  RUN(CMAESTestCase, rosenbrock);
  RUN(CMAESTestCase, himmelblau);
  RUN(CMAESTestCase, ellinum);
}

void CMAESTestCase::rosenbrock()
{
  OpenANN::IPOPCMAES cmaes;
  Rosenbrock<10> r;
  OpenANN::StopCriteria s;
  s.maximalFunctionEvaluations = 100000;
  s.maximalIterations = 10000;
  s.minimalValue = 0.001;
  s.maximalRestarts = 10;
  cmaes.setOptimizable(r);
  cmaes.setStopCriteria(s);
  cmaes.optimize();
  Vt optimum = cmaes.result();
  ASSERT(r.error() < 0.01);
}

void CMAESTestCase::himmelblau()
{
  OpenANN::IPOPCMAES cmaes;
  Himmelblau r;
  OpenANN::StopCriteria s;
  s.maximalFunctionEvaluations = 10000;
  s.maximalIterations = 10000;
  s.minimalValue = 0.001;
  cmaes.setOptimizable(r);
  cmaes.setStopCriteria(s);
  cmaes.optimize();
  Vt optimum = cmaes.result();
  ASSERT_WITHIN(r.error(), 0.0, 0.001);
}

void CMAESTestCase::ellinum()
{
  OpenANN::IPOPCMAES cmaes;
  Ellinum<3> r;
  OpenANN::StopCriteria s;
  s.maximalIterations = 10000;
  s.minimalValue = 0.01;
  cmaes.setOptimizable(r);
  cmaes.setStopCriteria(s);
  cmaes.optimize();
  Vt optimum = cmaes.result();
  ASSERT(!isInf(r.error()));
  ASSERT(!isNaN(r.error()));
}