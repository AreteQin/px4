px4_add_module(
	MODULE examples__px4_app
	MAIN px4_app
	SRCS
		px4_app.c
	DEPENDS
		px4_work_queue
	)
