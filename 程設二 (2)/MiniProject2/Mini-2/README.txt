# Installation：
1. Remember to change your library directory in project setting.

2. If you cannot run the project correctly, please first check your project setting.

3. You can also re-create a new project, and include all needed files into your new project.

=============================================================================================

#Tracing code：

1. For start scene, you can trace the following parts:

	> GameWindow::game_play()
	> GameWindow::game_begin()
	

2. For adding keyboard and mouse events, you can add them in the following parts:

	> GameWindow::process_event(): 
		...You can process events here
	
	> GameWindow::draw_running_map(): 
		...If you add pause functionality, maybe, you also need add some code here
		
3. For using slider to control volume of music, you can trace the following parts:

	> Slider::Drag()
	> Slider::getDegree()
	> Slider::isClicked()
	
	You should first check if target is clicked or not
	If clicked, then when cursor moves, update slider degree (by Slider::Drag()).
	Remember to toggle "dragged" to change the status of target.

4. For tower attacking behavior, you can trace the following parts:

	> GameWindow::game_update()
	> Tower::DetectAttack()
	> Tower::TriggerAttack()
	> Tower::UpdateAttack()
	
5. For customizing your own tower, you can use the following steps:

	> Copy any tower file that has been created by TAs.
	> Modify some variables to any values you want (but still meet the requirements)
	> Put tower images and attack images into a folder.
	> In GameWindow::create_tower(...), you should add some new cases into it.
	> In Menu::MouseIn(...), you also need to make user select tower by picture correctly.
	
	#Note: you can modify global.h for your convenience; or, you can just modify getWidth() and getHeight()