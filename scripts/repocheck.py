import argparse
import json
import os
import re
import urllib2

DESCRIPTION = """
The program compares the list of UVA solved problems (using UHUNT API), and
the list of source code files in the repository to see if there is any missing
files in the repository. It prints the list of problems that have been marked
as solved in UVA, but do not have corresponding source code files in the
repository. More details on UHUNT API can be found at:
http://uhunt.felix-halim.net/api
"""

DEFAULT_UNAME = "truongduy134"
UHUNT_UNAME_TO_UID_URL = "http://uhunt.felix-halim.net/api/uname2uid/{uname}"
UHUNT_USER_SUBS_URL = "http://uhunt.felix-halim.net/api/subs-user/{user-id}"
UHUNT_PROBLEM_LIST_URL = "http://uhunt.felix-halim.net/api/p"
UHUNT_UNAME_PARAM = "{uname}"
UHUNT_UID_PARAM = "{user-id}"
UHUNT_USER_SUBS_KEY = "subs"
UHUNT_ACCEPTED_CODE = 90
UHUNT_SUB_PROBLEM_ID_IND = 1    # index of problem id in submission response
UHUNT_SUB_VERDICT_ID_IND = 2    # index of verdict id in submission response
UHUNT_PROB_PROBLEM_ID_IND = 0   # index of problem id in problem list response
# index of problem number in problem list response
UHUNT_PROB_PROBLEM_NUM_IND = 1
DEFAULT_REPO_SRC_FILE_RE = "UVA(?P<problem_number>[0-9]+)(.)*"

def not_hidden_on_mac(dir_name):
    """ Returns true if the file / directory corresponding to input name is not
    hidden. The correctness is not guaranteed if the OS is not Mac OS.

    Args:
        dir_name : A string representing directory or file name

    Returns:
        True if the file / directory corresponding to the input name is hidden
        False otherwise
    """
    return not dir_name.startswith(".")

def get_dirs_in_dir(dir_path):
    """ Returns a list of directories directly under the specified directory
    Args:
        dir_path : Path to a directory

    Returns:
        A list of directory names directly under the input directory
    """
    return [name for name in os.listdir(dir_path)
            if not_hidden_on_mac(name) and
            os.path.isdir(os.path.join(dir_path, name))]

def get_files_in_dir(dir_path):
    """ Returns a list of file names directly under the specified directory
    Args:
        dir_path : Path to a directory

    Returns:
        A list of file names directly under the input directory
    """
    return [name for name in os.listdir(dir_path)
            if not_hidden_on_mac(name) and
            os.path.isfile(os.path.join(dir_path, name))]

def get_uva_id_to_number_mapping():
    """ Get a mapping from UVA problem id to UVA problem number
    Returns:
        A dictionary that maps a problem id to the problem number
    """
    uva_problems = json.load(urllib2.urlopen(UHUNT_PROBLEM_LIST_URL))
    id_to_number_map = {
        problem[UHUNT_PROB_PROBLEM_ID_IND]: problem[UHUNT_PROB_PROBLEM_NUM_IND]
        for problem in uva_problems
    }
    return id_to_number_map

def get_uva_accepted_problems(uva_username):
    """ Returns a list of distinct problem numbers of UVA problems with verdict
    ACCEPTED corresponding to the input username

    Args:
        uva_username : A string which is a UVA username

    Returns:
        A set of distinct problem ids solved by the input user
    """
    id_to_number_map = get_uva_id_to_number_mapping()
    uva_uid = json.load(urllib2.urlopen(
        UHUNT_UNAME_TO_UID_URL.replace(UHUNT_UNAME_PARAM, uva_username)))
    subs_json = json.load(urllib2.urlopen(
        UHUNT_USER_SUBS_URL.replace(UHUNT_UID_PARAM, str(uva_uid))))
    submissions = subs_json[UHUNT_USER_SUBS_KEY]
    accepted_lst = [id_to_number_map[sub[UHUNT_SUB_PROBLEM_ID_IND]]
                    for sub in submissions
                    if sub[UHUNT_SUB_VERDICT_ID_IND] == UHUNT_ACCEPTED_CODE]
    return set(accepted_lst)

def get_repo_problems(root_dir, filename_re=None):
    """ Returns all UVA problems ids in the repository. Assume the problem
    numbers can be retrieved from the source code file names.

    Args:
        root_dir : path to the root directory of the repository

    Returns:
        A set of distinct problem numbers in the repository
    """
    filename_re = filename_re or DEFAULT_REPO_SRC_FILE_RE
    problem_number_set = set()
    file_list = get_files_in_dir(root_dir)
    for filename in file_list:
        match_result = re.match(filename_re, filename)
        if match_result:
            problem_number_set.add(int(match_result.group("problem_number")))
    for child_dirname in get_dirs_in_dir(root_dir):
        child_path = os.path.join(root_dir, child_dirname)
        problem_number_set |= get_repo_problems(child_path, filename_re)
    return problem_number_set

def main():
    """ Main function to finds and prints the list of problems that have been
    marked as solved in UVA, but do not have corresponding source code files
    in the repository
    """
    # Command-line argument passing
    parser = argparse.ArgumentParser(description=DESCRIPTION)
    parser.add_argument(
        "--dir", "-d",
        nargs=1,
        type=str,
        default=os.getcwd(),
        help="Path to the directory where all source code files can be found. "
             "It is ok for source code files are in some subdirectory. "
             "The program goes to every descendant subdirectories "
             "to find the files."
    )
    parser.add_argument(
        "--uname", "-u",
        nargs=1,
        type=str,
        default=DEFAULT_UNAME,
        help="UVA username whose list of UVA solved problems is retrieved."
    )
    parser.add_argument(
        "--regex", "-r",
        nargs=1,
        type=str,
        default=DEFAULT_REPO_SRC_FILE_RE,
        help="The regular expression to indicating the format of source code "
             "files in the repository. The regular expression should indicate "
             "a group with id problem_number so that the program can extract "
             "UVA problem ids from file names. For example, if default "
             "names for source code files are UVA101.cpp, UVA1911.java, etc., "
             "then the regular expression can be "
             "\"UVA(?P<problem_id>[0-9]+)(.)*\""
    )
    args = parser.parse_args()
    root_dir = args.dir[0] if type(args.dir) is list else args.dir

    # Main computation
    print "Retrieving list of accepted UVA problems of user %s..." % args.uname
    accepted_numbers = get_uva_accepted_problems(args.uname)
    print "Retrieving list of UVA source code files in the repository %s..." % (
        root_dir)
    repo_numbers = get_repo_problems(root_dir, args.regex)
    repo_missing_numbers = sorted(list(accepted_numbers - repo_numbers))

    # Printing output messages
    if repo_missing_numbers:
        message = "List of UVA accepted problems that do not have source code "\
                  "in the repository:\n"
        message += "%s\n" % ",".join(
            [str(problem_number) for problem_number in repo_missing_numbers])
        num_missing = len(repo_missing_numbers)
        message += "In total, %d %s missing." % (
            num_missing,
            "is" if num_missing == 1 else "are")
        print message
    else:
        print "No missing UVA source code files"

if __name__ == "__main__":
    main()
