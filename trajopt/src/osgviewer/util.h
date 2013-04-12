#ifndef __UTIL_H__
#define __UTIL_H__

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <osg/Vec3d>
#include <osg/Geometry>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "plotting.h"

using namespace std;

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

void setGlobalEnv(Environment::Ptr env);
Environment::Ptr getGlobalEnv();

void toggle(bool* b);
void add(int* n, int increment);

namespace util {


  ///////////////// CONVERSIONS ////////////////////////////
  inline osg::Vec3d toOSGVector(const Eigen::Vector3f &v) { return osg::Vec3d(v.x(), v.y(), v.z()); }
  inline Eigen::Vector3f toEigenVector(const osg::Vec3d &v) { return Eigen::Vector3f(v.x(), v.y(), v.z()); }
  osg::ref_ptr<osg::Vec3Array> toVec3Array(const std::vector<Eigen::Vector3f>&);
  osg::ref_ptr<osg::Vec4Array> toVec4Array(const std::vector<Eigen::Vector4f>&);
  osg::ref_ptr<osg::Vec3Array> toVec3Array(const Eigen::MatrixXf& in);
  osg::ref_ptr<osg::Vec4Array> toVec4Array(const Eigen::MatrixXf& in);

  // Nan/Inf checking
  inline bool isfinite(const Eigen::Vector3f &v) {
      return std::isfinite(v.x()) && std::isfinite(v.y()) && std::isfinite(v.z());
  }

  inline bool isfinite(const Eigen::Matrix3f &m) {
      return isfinite(m.col(0)) && isfinite(m.col(1)) && isfinite(m.col(2));
  }

  inline bool isfinite(const Eigen::Affine3f &t) {
      return isfinite(t.linear()) && isfinite(t.translation());
  }

  ///////////////// PLOTTING FOR DEBUGGING ////////////////////////////
  //These plot and remain in the environment

  void setGlobalEnv(Environment::Ptr env);
  Environment::Ptr getGlobalEnv();

  std::vector<float> toVec(const Eigen::VectorXf& in);
  Eigen::MatrixXf toEigenMatrix(const std::vector<Eigen::Vector3f>& in);

  void drawSpheres(vector<Eigen::Vector3f> points, Eigen::Vector3f color, float alpha, float radius, Environment::Ptr env);
  void drawSpheres(Eigen::Vector3f point, Eigen::Vector3f color, float alpha, float radius, Environment::Ptr env);
  void drawLines(vector<Eigen::Vector3f> points0, vector<Eigen::Vector3f> points1, Eigen::Vector3f color, float alpha, Environment::Ptr env);
  void drawPoly(vector<Eigen::Vector3f> points, Eigen::Vector3f color, float alpha, Environment::Ptr env);
  void drawAxes(Eigen::Affine3d transform, float size, Environment::Ptr env);
}

#endif // __UTIL_H__
