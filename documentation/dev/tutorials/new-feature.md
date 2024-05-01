## Tutorial 1.
### How-to: Add branches, work with branches, commit changes to branches, merge, send pull requests and link commits to GitHub Project's issue tracker tickets

#### This is a project-specific tutorial, where I (alexamarki) assume that you (the contibutor) have imported this project to your IDE from the github repo. This is why we suppose that the "main" and "development" branches are present
##### For VSCode users:
1. Open the "Source control" tab and click "Clone repository"
2. After linking the repo you wish to clone (this one) and logging into github, you should be all set!
##### Branching (USE THE BUILT-IN IDE TERMINAL)
1. By default, you will be in the "main" branch. To switch to another branch (as you SHOULD, since _DEVELOPING_ in main is **dangerous**), you should use the ```git checkout branchname``` command, where ```branchname``` should be replaced by the name of the branch you are switching to. [That branch, in our case, is "development"]
2. From here, switch to a branch created for the development of the feature you're working on. If there is no such branch as of yet, use the ```git branch branchname``` command, followed by the aforementioned "checkout" command.
3. When you are ready to commit changes to this branch, simply commit the changes using the built-in IDE UI for such operations OR execute the "git commit" command.
4. You might want to periodically push these commits to the remote version of the branch. The usual command for this is ```git push origin branchname```. However, if you have just created the branch "branchname", you should add an argument that will create a similar branch remotely: ```git push --set-upstream origin main```
5. Suppose another branch (i.e., main) gets an update. You might want to keep up with the changes in that branch, so you should periodically run ```git pull origin main``` in your dev branch throughout your development process in order to not experience a versioning conflict. You should also periodically run ```git fetch origin``` to update your local main branch, as well as all the other branches. VSCode may prompt to do that for you in the background - you can choose to agree to that if you wish.
6. Once you have finished working on the feature you have been developing in your branch and **YOU ARE CERTAIN IT IS WORKING AS INTENDED**, use ```git checkout development``` to return back to the main branch. There, run ```git merge branchname```.
7. Finally, run ```git push origin development```.
8. Once you open github, it will most likely ask you to create a pull request. From there, that PR can be linked to an issue from GitHub Projects and then that PR may be accepted.
9. Once the PR is accepted, and every update is merged, you're good to go and work on another feature.
10. Once the completed features in "development" are substantial enough for a release in "main", steps 6 and 7 may be repeated for main instead of development. This, however, requires the agreement of the whole team.

##### FYI the branch structure in our case is:
##### main ---------------------------------------
##### ..........\\_development__________________________
##### ................\\_feature1__...  \\___feature2___...