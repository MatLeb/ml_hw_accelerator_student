# Python class to help git operation like pull, push, commit, create branch, rebase from main branch, etc.
# using module gitpython
# --------------------------------------------------------------------

import os
import shutil
import git
import subprocess
import sys
import time
from datetime import datetime
from git import Repo
from git import Git
from git import RemoteProgress
from git import InvalidGitRepositoryError
from git import NoSuchPathError
from git import GitCommandError
from git import GitCommandNotFound
from git import GitCommandError

# --------------------------------------------------------------------
# Path: script/gitHelper.py
# --------------------------------------------------------------------


class GitHelper:
    
        # --------------------------------------------------------------------
    
        def __init__(self, path):
            self.path = path
            self.repo = None
            self.git = None
            self.remote = None
            self.remote_name = None
            self.remote_url = None
    
            try:
                self.repo = Repo(path)
                self.git = self.repo.git
                self.remote = self.repo.remote()
                self.remote_name = self.remote.name
                self.remote_url = self.remote.url
            except InvalidGitRepositoryError:
                print("InvalidGitRepositoryError: " + path)
            except NoSuchPathError:
                print("NoSuchPathError: " + path)
            except GitCommandError:
                print("GitCommandError: " + path)
            except GitCommandNotFound:
                print("GitCommandNotFound: " + path)
    
        # --------------------------------------------------------------------
    
        def print_header(self, header):
            print("-" * 80)
            print("[STEP] " + header)
            print("-" * 80)
    
        # --------------------------------------------------------------------
    
        def pull(self):
            self.print_header("Pull git repository in " + self.path + ":")
            # pull latest version from git in export directory
            self.git.pull()
            # reset all changes in export directory
            self.git.reset("--hard", "HEAD")
    
        # --------------------------------------------------------------------
    
        def status(self):
            self.print_header("Git status in " + self.path + ":")
            # display git status in export directory
            self.git.status()
    
        # --------------------------------------------------------------------
    
        def add(self, file):
            self.print_header("Git add " + file + " in " + self.path + ":")
            # add file to git
            self.git.add(file)

        # --------------------------------------------------------------------
        # Add all files to git

        def add_all(self):
            self.print_header("Git add all files in " + self.path + ":")
            # add file to git
            self.git.add(".")
    
        # --------------------------------------------------------------------
    
        def commit(self, message):
            self.print_header("Git commit with message \"" + message +
                            "\" in " + self.path + ":")
            # commit file to git
            self.git.commit("-m", message)
    
        # --------------------------------------------------------------------
    
        def push(self):
            self.print_header("Git push in " + self.path + ":")
            # push file to git
            self.git.push()
    
        # --------------------------------------------------------------------
    
        def create_branch(self, branch_name):
            self.print_header("Git create branch " + branch_name +
                            " in " + self.path + ":")
            # create branch
            self.git.checkout("-b", branch_name)
    
        # --------------------------------------------------------------------
    
        def checkout_branch(self, branch_name):
            self.print_header("Git checkout branch " + branch_name +
                            " in " + self.path + ":")
            # checkout branch
            self.git.checkout(branch_name)

        # --------------------------------------------------------------------
        # save local changes to current branch, update the main branch, and rebase
        # from main branch

        def rebase_from_main(self, main_branch_name):
            self.print_header("Git rebase from main branch " + main_branch_name +
                            " in " + self.path + ":")
            # save local changes to current branch
            self.git.add(".")
            self.git.commit("-m", "save local changes")
            # update the main branch
            self.git.checkout(main_branch_name)
            self.git.pull()
            # rebase from main branch
            self.git.checkout("-")
            self.git.rebase(main_branch_name)
            # push file to git
            self.git.push()
            # Display in green the active branch
            print("\033[92m" + "Active branch: " + self.repo.active_branch.name + "\033[0m")

        # --------------------------------------------------------------------
        # Ask the new branch name and create this branch from main branch

        def create_branch_from_main(self, main_branch_name):
            self.print_header("Git create branch from branch " + main_branch_name +
                            " in " + self.path + ":")
            # Ask the new branch name
            branch_name = input("Enter the new branch name: ")
            # create branch from main branch
            # check if branch branch_name already exists
            if branch_name in self.repo.branches:
                print("Branch " + branch_name + " already exists")
                self.git.checkout(branch_name)
                self.git.pull()
            else:
                print("Creating branch " + branch_name)
                self.git.checkout("-b", branch_name)
                self.git.push("--set-upstream", "origin", branch_name)
            # Display in green the active branch
            print("\033[92m" + "Active branch: " + self.repo.active_branch.name + "\033[0m")

# --------------------------------------------------------------------
# main fonction that uses the class GitHelper to perform git operation
# in a script with options parsed from command line with argparse
# --------------------------------------------------------------------

if __name__ == "__main__":

    # --------------------------------------------------------------------
    # Parse command line options
    # --------------------------------------------------------------------

    import argparse

    parser = argparse.ArgumentParser(description="Git helper script to perform git operation")
    parser.add_argument("-rp", "--root_path", help="Path to git repository", default=".")
    parser.add_argument("-m", "--main", help="Main branch name", default="main")
    parser.add_argument("-c", "--create", help="Create a new branch from main branch", action="store_true")
    parser.add_argument("-r", "--rebase", help="Rebase from main branch", action="store_true")
    parser.add_argument("-a", "--add", help="Add file to git", action="store_true")
    parser.add_argument("-al", "--add_all", help="Add all files to git", action="store_true")
    parser.add_argument("-s", "--status", help="Display git status", action="store_true")
    parser.add_argument("-u", "--pull", help="Pull from git", action="store_true")
    parser.add_argument("-o", "--checkout", help="Checkout branch", action="store_true")
    parser.add_argument("-b", "--branch", help="Branch name")
    parser.add_argument("-f", "--file", help="File name")
    parser.add_argument("-g", "--commit", help="Commit file to git")
    parser.add_argument("-p", "--push", help="Push file to git", action="store_true")
    parser.add_argument("-bfm", "--branch_from_main", help="Create branch from main branch", action="store_true")
    parser.add_argument("-rfm", "--rebase_from_main", help="Rebase from main branch", action="store_true")
    args = parser.parse_args()

    # --------------------------------------------------------------------
    # Create GitHelper object
    # --------------------------------------------------------------------

    git_helper = GitHelper(args.root_path)

    # --------------------------------------------------------------------
    # Perform git operation
    # --------------------------------------------------------------------

    if args.create:
        git_helper.create_branch_from_main(args.main)
    elif args.rebase:
        git_helper.rebase_from_main(args.main)
    elif args.add:
        git_helper.add(args.file)
    elif args.status:
        git_helper.status()
    elif args.pull:
        git_helper.pull()
    elif args.checkout:
        git_helper.checkout_branch(args.branch)
    elif args.commit:
        git_helper.commit(args.commit)
    elif args.push:
        git_helper.push()
    elif args.add_all:
        git_helper.add_all()
    elif args.branch_from_main:
        git_helper.create_branch_from_main(args.main)
    elif args.rebase_from_main:
        git_helper.rebase_from_main(args.main)
    else:
        print("No option selected")
