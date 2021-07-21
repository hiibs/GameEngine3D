# Install script for directory: F:/dev/Leka3D/ext/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Leka3d")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/dev/Leka3D/build/ext/assimp/lib/Debug/assimp-vc142-mtd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/dev/Leka3D/build/ext/assimp/lib/Release/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/dev/Leka3D/build/ext/assimp/lib/MinSizeRel/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/dev/Leka3D/build/ext/assimp/lib/RelWithDebInfo/assimp-vc142-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/anim.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/aabb.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/ai_assert.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/camera.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/color4.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/color4.inl"
    "F:/dev/Leka3D/build/ext/assimp/code/../include/assimp/config.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/ColladaMetaData.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/commonMetaData.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/defs.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Defines.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/cfileio.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/light.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/material.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/material.inl"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/matrix3x3.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/matrix3x3.inl"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/matrix4x4.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/matrix4x4.inl"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/mesh.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/pbrmaterial.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/postprocess.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/quaternion.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/quaternion.inl"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/scene.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/metadata.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/texture.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/types.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/vector2.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/vector2.inl"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/vector3.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/vector3.inl"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/version.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/cimport.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/importerdesc.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Importer.hpp"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/DefaultLogger.hpp"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/ProgressHandler.hpp"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/IOStream.hpp"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/IOSystem.hpp"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Logger.hpp"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/LogStream.hpp"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/NullLogger.hpp"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/cexport.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Exporter.hpp"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/DefaultIOStream.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/DefaultIOSystem.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/SceneCombiner.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/fast_atof.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/qnan.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/BaseImporter.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Hash.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/ParsingUtils.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/StreamReader.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/StreamWriter.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/StringComparison.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/StringUtils.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/SGSpatialSort.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/GenericProperty.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/SpatialSort.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/SmallVector.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/SmoothingGroups.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/SmoothingGroups.inl"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/StandardShapes.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/RemoveComments.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Subdivision.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Vertex.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/LineSplitter.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/TinyFormatter.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Profiler.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/LogAux.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Bitmap.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/XMLTools.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/IOStreamBuffer.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/CreateAnimMesh.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/XmlParser.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/BlobIOSystem.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/MathFunctions.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Exceptional.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Compiler/poppack1.h"
    "F:/dev/Leka3D/ext/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/dev/Leka3D/build/ext/assimp/code/Debug/assimp-vc142-mtd.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/dev/Leka3D/build/ext/assimp/code/RelWithDebInfo/assimp-vc142-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

