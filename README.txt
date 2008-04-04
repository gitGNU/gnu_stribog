Copyright (C) 2005, 2006, 2007, 2008
 Ineiev <ineiev@users.sourceforge.net>, super V 93
See the end of the file for license conditions.

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

COPYING file has not been removed
for political reasons.

NOTES ON BRANCHES AND REVISIONS

Each branch should have a text file named 'branch'
in the root directory. from this file the name
of current branch (possibly with it's predecessors)
and the purpose of the branch can be learnt.

The revisions are named within the build system
(configure.ac files) like 0.MAJOR.MINOR[-suffix]
where MAJOR is the release branch number, MINOR is
the number of release on the branch, optional suffix
means unstable releases (rc[0-9]*) or marks interrelease
revisions (minus), e.g.

0.1.2-rc2-minus means a revision between 0.1.2-rc1 and
0.1.2-rc2.

0.1.2-rc[0-9]* preceeds stable version named 0.1.2

trunc revisions are named like 0.1-minus, which means
that the branch 0.1 is the next revision branch
that to be forked out.

Git is branched and tagged accordingly.
eventually a branch named 0.1 is created from trunc,
and the revision in configure.ac is set to 0.1.1-rc0-minus.
then release candidates 0.1.0-rc1, 0.1.0-rc2 and so on 
are released and at last release 0.1.0 is published.
after that the release name is changed to 0.1.2-rc0-minus

All release and release candidates should be tagged with
their numbers (e.g. 0.1.2-rc1); these tags should be
signed like this:
$ git tag -s -m "release candidate" 0.1.2-rc1

HOW TO USE GIT (basic invocations)

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

For anonymous access, use these:

$ git clone git://git.savannah.nongnu.org/stribog.git
 to make your local repository

$ git checkout -b trunc origin/trunc
 to make a local branch trunc based on fetched origin/trunc

$ git fetch
 to update copies of remote branches

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

This file is part of stribog.

Stribog is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
