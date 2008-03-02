This branch contains meta-documentation
on using Git branches, revisions and so on. 
here you can read about history and purposes of Git branches
of the project.

To get a real working directory you should
checkout another branch.

Description of currently existing branches is
maintained in Git.branches.txt file

ChangeLog contains a log of creating-removing-merging
the branches

COPYING and copyright files have not been removed
for clarity reasons.

HOW TO USE GIT

Git is the revision control system used by the project.

Here is a typical ~/.gitconfig file contents
(please replace the names and email with yours):
<<<EOF
[user]
 name = Ineiev (favourite host)
 email = ineiev@users.sourceforge.net
[core]
 editor = vim
EOF

If you are a maintainer, your usual spells are
(replace ineiev with your login name)

$ git clone ineiev@git.savannah.nongnu.org:/srv/git/stribog.git
 to get a new local repository

$ git remote add savannah ineiev@git.savannah.nongnu.org:/srv/git/stribog.git
 to add a reference for the public repository

$ git push savannah feb2008
 to push into savannah local branch named 'feb2008' 
 (non-existent will be created)

$ git push savannah
 to push into savannah all local branches

$ git push savannah :refs/heads/feb2008
 to remove branch feb2008 from remote savannah

For anonymous access, use these:

$ git clone git://git.savannah.nongnu.org/stribog.git
 to make your local repository

$ git checkout -b feb2008 origin/feb2008
 to make a local branch feb2008 based on fetched origin/feb2008

$ git fetch
 to update copies of remote branches

$ git pull
 to fetch all remote branches and merge
 one of them into your current branch

Common to both access types:

$ git checkout master
 to switch to existing branch 'master'

$ git add .
 to cache the changes in your files against
 the current branch most recent commit

$ git diff
 to see what will be "git add"ed

$ git diff --cached
 to see what has been "git add"ed but not 
 "git commit"ed

$ git branch
 to list the local repository branches

$ git branch -r
 to list the public repositories branches

$git commit
 to move the changes to your current branch

$git show
 to see the latest commit description
