
#ifndef H_USER_MSGS_BENNIS_20130218
#define H_USER_MSGS_BENNIS_20130218

enum {
    GUI_MSG_USER_GESTURE_MODULE_START   = GUI_MSG_USER_GESTURE_START,   // For gesture
    GUI_MSG_USER_GESTURE_MODULE_END     = GUI_MSG_USER_GESTURE_END,

    GUI_MSG_USER_REPAINT_NEIGHBOR       = (GUI_MSG_USER_DEF + 0x40),     // External used message
    GUI_MSG_USER_WIN_CHANGE             = (GUI_MSG_USER_DEF + 0x41),
    GUI_MSG_USER_STANDY                 = (GUI_MSG_USER_DEF + 0x42),
    GUI_MSG_USER_WIN_TIMER              = (GUI_MSG_USER_DEF + 0x43)
};

#endif

