# Puzzle-based / survival mobile game


#How to set up this project

Project is shipped without third-party libraries, frameworks and datapack.
That actually means developer has to complete some setup after project checkout to
get software work.

Please follow these steps to build and run game on your machine:

1. clone project to your local directroy, let's call it "game"
2. install dependecies (please see Dependencies section for details)
3. accroding to platfrom you use select correspnding path in "game". 
    For example to build project for IOS device go to "proj.ios_mac" folder
4. follow Cocos2D instructions to setup project

#Dependencies

1. Cocos2d-x (http://www.cocos2d-x.org) 
	version _3.9_ (https://github.com/cocos2d/cocos2d-x/tree/V3.9)
2. Download Cocos2d of specified version and copy it to your "game" folder as "cocos2d" folder
3. Datapack is included as sub-module. Please read GIT manual how to checkout porject with sub-modules

#How to start work with repo

1. Fork repository to your own github account
2. Clone project to your local dir
	git clone https://github.com/<your github acc>/game.git
3. Init resource submodule
	git submodule init
4. Update resources
	git submodule update

#How to sync with main repo

1. For sync with main repository, use command add upstream (you need to do this step only once)
	git remote add upstream https://github.com/TopSecretGames/game.git
2. Fetch all remotes
	git fetch -all
3. Checkout to your local master
	git checkout master
4. Merge remote changes with your local branch
	git merge upstream/master

#Notes for contributors

Code formatting:
We respect netty codding and that's why we use Google-code style. 
To keep code well-formated we preffer to util <code>clang-format</code> 3.8.0

Change requests (CR):
We use CR's to:
- add/mod/remove design-affecting components, that is those components which depend on, or dependent by other system components
- add/mod/remove any public contracts

It's _strictly_ _prohibited_ to make any changes on mentioned above points without corresponding CR.

Test:
We are TDD adepts. We deny untested, fragile code. Please read about TDD carefully before you start.

Forks:
Push to master directly is not allowed. We preffer forks. To make a contribution u have to fork firstly, make a change, push it to your fork, create pull request and wait for approve and merge.
If your PR is conflicting with existing code or just can't be merge for some any other reason it will be rejected.
We will be really happy, if you put issue numbers (via github hashtag) to yours commit messages.

