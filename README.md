# Python Strings for C++
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/88e014aae022466aa04a5e91018f83af)](https://www.codacy.com/app/AlexanderJDupree/Python-Strings-for-CPP?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=AlexanderJDupree/Python-Strings-for-CPP&amp;utm_campaign=Badge_Grade)
[![Build Status](https://travis-ci.org/AlexanderJDupree/Python-Strings-for-CPP.svg?branch=master)](https://travis-ci.org/AlexanderJDupree/Python-Strings-for-CPP)
[![codecov](https://codecov.io/gh/AlexanderJDupree/Python-Strings-for-CPP/branch/master/graph/badge.svg)](https://codecov.io/gh/AlexanderJDupree/Python-Strings-for-CPP)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/AlexanderJDupree/Python-Strings-for-CPP/master/LICENSE)

- [Introduction](#Introduction)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Execute unit tests](#execute-unit-tests)
- [Built With](#built-with)
- [Contributing](#contributing)
- [Versioning](#versioning)
- [Authors](#authors)
- [License](#license)

## Introduction

As someone who learned Python before C++, one of my biggest complaints was how C++ handled strings. In Python, strings were so versatile and was accompanied by a variety of useful methods. Not so much for std::string in C++. Even though std::string performs fine, and it isn't too hard to manipulate it to my needs, I wanted to undertake this project to create a more Pythonic string class for C++. 

06.15.2018

It is my hope, that in the coming weeks I will be able to generate a single-header include that will perform similarly to std::string, whilst containing the functionality and methods that Python strings possess.

01.12.2019

My university studies have really ate up a lot of my time and thus, I have not been able to flesh out or work on this project as much as I would like. My latest commit, over a month ago, did refactor the entire project into reference-counted, immutable strings which is more in the fashion of python strings. It will be my focus over the next coming weeks to set up a roadmap and issue tracker such that I will be able to pickup and work on this project at my leisure and open it up to would-be contributors. 

## Getting Started
## Usage
## Execute unit tests
## Built With

* [Catch2](https://github.com/catchorg/Catch2) - Unit Testing framework. If you haven't checked it out, do it. It's seriously awesome. 

## Contributing

Please read [CONTRIBUTING.md](https://github.com/AlexanderJDupree/Python-Strings-for-CPP/blob/master/CONTRIBUTING.md) for details on our code of conduct.

All contributions are welcome: bug fixes, recommendations, issues, features.

Plase see the [issues](https://github.com/AlexanderJDupree/Python-Strings-for-CPP/issues) before you submit a pull request or raise an issue to avoid duplication. 

To contribute to this repository:

- [Fork the project to your own GitHub profile](https://help.github.com/articles/fork-a-repo/)

- Download the project using git clone:
```
git clone git@github.com:<YOUR_USERNAME>/Python-Strings-for-CPP.git
```
- Create a new branch with a descriptive name:
```
git checkout -b descriptive_branch_name
```
- Write some code, fix something, and add a test to prove that it works. **No pull request will be accepted without tests passing, or without new tests if new features are added.**

- Commit your code and push it to GitHub

- [Open a new pull request](https://help.github.com/articles/creating-a-pull-request/) and describe the changes you have made.

- We'll accept your changes after review.

Simple!
## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/AlexanderJDupree/LinkedListsCPP/tags). 

## Authors
* **Alexander DuPree** - *Initial work* - [GitHub](https://github.com/alexanderjdupree)

See also the list of [contributors](https://github.com/AlexanderJDupree/Python-Strings-for-CPP/graphs/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](https://raw.githubusercontent.com/AlexanderJDupree/Python-Strings-for-CPP/master/LICENSE) file for details

## Special Thanks

This readme and the contributing guidelines are based off this great [template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
