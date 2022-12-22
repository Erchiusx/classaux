# classaux
A system that aids students in course choosing

排课信息更新方式：
全局变量timetable为时间表整体，timetable.display()清除时间表上的所有排课信息，timetable.display( plan )接受一个带洞的数组，索引为0-6，每一项为一个索引为0-4的带洞数组，数组的每一项为一个对象，包含显示在课程表上的所有信息：
classname: 课程名
classID: 课程序号
Teacher: 课程教师
