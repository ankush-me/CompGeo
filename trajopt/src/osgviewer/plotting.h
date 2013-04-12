#pragma once

#include <Eigen/Dense>
#include "environment.h"
#include <iostream>
#include <vector>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/StateSet>


class PlotObject : public EnvironmentObject {
protected:
  osg::Vec4 m_defaultColor;
  osg::ref_ptr<osg::Geometry> m_geom;
  osg::ref_ptr<osg::Geode> m_geode;
public:
  typedef boost::shared_ptr<PlotObject> Ptr;

  void clear();

  virtual void init(){
    getEnvironment()->osg->root->addChild(m_geode.get());
  }

  void preDraw(){};
  void destroy(){}
  void setDefaultColor(float r, float g, float b, float a);
  void forceTransparency(float a);
};


class PlotPoints : public PlotObject {
  osg::ref_ptr<osg::Vec4Array> colors;
public:
  typedef boost::shared_ptr<PlotPoints> Ptr;
  PlotPoints(float size=5);
  void setPoints(const osg::ref_ptr<osg::Vec3Array>& osgPts, const osg::ref_ptr<osg::Vec4Array>& osgCols);
  void setPoints(const osg::ref_ptr<osg::Vec3Array>& osgPts);
  void setPoints(const std::vector<Eigen::Vector3f>& pts, const std::vector<Eigen::Vector4f>& cols);
  void setPoints(const std::vector<Eigen::Vector3f>& pts);
  void forceTransparency(float a);
};



class PlotLines : public PlotObject {
public:
  typedef boost::shared_ptr<PlotLines> Ptr;
  PlotLines(float width=5);
  void setPoints(const std::vector<Eigen::Vector3f>& pts, const std::vector<Eigen::Vector4f>& cols);
  void setPoints(const std::vector<Eigen::Vector3f>& pts);
  void setPoints(const osg::ref_ptr<osg::Vec3Array>& pts, const osg::ref_ptr<osg::Vec4Array>& cols);
  void setPoints(const osg::ref_ptr<osg::Vec3Array>& pts);
  void forceTransparency(float a);
};



class PlotSpheres : public EnvironmentObject  {
public:
  typedef boost::shared_ptr<PlotSpheres> Ptr;

  osg::ref_ptr<osg::Geode> m_geode;
  int m_nDrawables;

  void clear();

  virtual void init(){
    getEnvironment()->osg->root->addChild(m_geode.get());
  }
  void preDraw(){}
  void destroy(){}    

  PlotSpheres();
  // void setDefaultColor(float r, float g, float b, float a);    
  void plot(const osg::ref_ptr<osg::Vec3Array>& centers, const osg::ref_ptr<osg::Vec4Array>& cols, const std::vector<float>& radii);

};


class PlotBoxes : public EnvironmentObject {
public:
  typedef boost::shared_ptr<PlotBoxes> Ptr;

  osg::ref_ptr<osg::Geode> m_geode;

  virtual void init() {
    getEnvironment()->osg->root->addChild(m_geode.get());
  }
  void preDraw(){}
  void destroy() {
    getEnvironment()->osg->root->removeChild(m_geode.get());
  }

  PlotBoxes();
  void clear();
  void addBox(const osg::Vec3 &center, float lenx, float leny, float lenz, const osg::Vec4 &color);
};


class PlotAxes : public PlotLines {
public:
  typedef boost::shared_ptr<PlotAxes> Ptr;
  PlotSpheres::Ptr m_ends;

  virtual void init(){
    getEnvironment()->osg->root->addChild(m_geode.get());
    getEnvironment()->osg->root->addChild(m_ends->m_geode.get());
  }

  PlotAxes() {  m_ends.reset(new PlotSpheres());}
  PlotAxes(osg::Vec3f origin, osg::Vec3f x, osg::Vec3f y, osg::Vec3f z, float size);
  void setup(osg::Vec3f origin, osg::Vec3f x, osg::Vec3f y, osg::Vec3f z, float size);
  void setup(const Eigen::Affine3f &tf, float size);
  void clear();
};


class PlotCurve : public osg::Geode {
public:
  typedef osg::ref_ptr<PlotCurve> Ptr;
  osg::Vec4 m_defaultColor;
  osg::ref_ptr<osg::Geometry> m_geom;

  PlotCurve(float width=5);
  void setPoints(const std::vector<Eigen::Vector3f>& pts, const std::vector<Eigen::Vector4f>& cols);
  void setPoints(const std::vector<Eigen::Vector3f>& pts);
  void setPoints(const osg::ref_ptr<osg::Vec3Array>& pts, const osg::ref_ptr<osg::Vec4Array>& cols);
  void setPoints(const osg::ref_ptr<osg::Vec3Array>& pts);
};
