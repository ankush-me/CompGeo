/** Provides various geometric predicates like orientation tests.*/

#pragma once
#include <Eigen/Dense>

double orient2d (Eigen::Vector2d pa, Eigen::Vector2d pb, Eigen::Vector2d pc);
bool ccw(Eigen::Vector2d pa, Eigen::Vector2d pb, Eigen::Vector2d pc) ;
bool ccw(Eigen::Vector2f pa, Eigen::Vector2f pb, Eigen::Vector2f pc);
