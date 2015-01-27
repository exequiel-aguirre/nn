import bpy, sys

bpy.ops.import_scene.obj(filepath=sys.argv[-1])

bpy.ops.object.select_pattern(pattern="human:HighPolyEyes",extend=False)
bpy.ops.object.delete()


bpy.ops.object.select_all(action='SELECT')
bpy.context.scene.objects.active = bpy.data.objects["human:Tshirt01"]
bpy.ops.object.join()

#bpy.data.objects["human:Tshirt01"].name= "human"
bpy.ops.object.origin_set(type='GEOMETRY_ORIGIN')


bpy.ops.export_scene.obj(filepath=sys.argv[-1],use_normals=True,use_uvs=True,use_materials=False,use_triangles=True)
