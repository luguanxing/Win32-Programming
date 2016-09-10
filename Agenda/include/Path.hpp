#ifndef PATH_HPP
#define PATH_HPP

class Path {
public:
    /**
     * user.csv path
     */
    static const char *userPath;

    /**
     * meeting.csv path
     */
    static const char *meetingPath;
};

const char *Path::meetingPath = "data/meetings.csv";
const char *Path::userPath = "data/users.csv";


#endif
