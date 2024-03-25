// #include "LoadFastObjMeshOperation.hpp"
//
// void LoadFastObjMeshOperation::LoadModel()
// {
// 	fastObjMesh = fast_obj_read(filePath.c_str());
// }
//
// LoadFastObjMeshOperation::LoadFastObjMeshOperation(const std::string& filePath): filePath(filePath)
// {
// 	thread = std::thread(&LoadModel, this);
// }
//
// fastObjMesh* LoadFastObjMeshOperation::AwaitResult()
// {
// 	thread.join();
// 	return fastObjMesh;
// }
