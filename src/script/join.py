import bpy, sys

bpy.ops.import_scene.obj(filepath=sys.argv[-1])

#bpy.ops.object.select_pattern(pattern="human:HighPolyEyes",extend=False)
#bpy.ops.object.delete()

#select all and make one active
bpy.ops.object.select_all(action='SELECT')
bpy.context.scene.objects.active = bpy.data.objects["human2:Body"]
#join
bpy.ops.object.join()

#move to origin
bpy.data.objects["human2:Body"].name= "human"
bpy.ops.object.origin_set(type='GEOMETRY_ORIGIN')

#scale
bpy.data.objects["human"].scale =(0.71,0.71,0.71)
bpy.ops.object.transform_apply(scale=True)


bpy.ops.export_scene.obj(filepath=sys.argv[-1],use_normals=True,use_uvs=True,use_materials=False,use_triangles=True)
