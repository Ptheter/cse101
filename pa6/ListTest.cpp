/***
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA6
* ListTest.cpp
* Test file for List ADT.
***/


#include<iostream>
#include<string>
#include<stdexcept>

#include"List.h"

using namespace std;

int main() {

  List A, B, C, D, G, H, I;
  int i, n = 10;

  // Testing insertAfter()
  for (i = 1; i <= n; i++) {
    A.insertAfter(i);
    B.insertAfter(11 - i);
    C.insertBefore(i);
    D.insertBefore(11 - i);
    G.insertBefore(i);
    H.insertBefore(i);
    I.insertBefore(i);
  }

  // Testing to_string()
  std::cout << "A = " << A.to_string() << std::endl;
  std::cout << "B = " << B.to_string() << std::endl;
  std::cout << "C = " << C.to_string() << std::endl;
  std::cout << "D = " << D.to_string() << std::endl;

  // Testing moveBack() and moveFront()
  A.moveBack();
  B.moveBack();
  C.moveFront();
  D.moveFront();

  // Testing position()
  std::cout << "A.position() = " << A.position() << std::endl;
  std::cout << "B.position() = " << B.position() << std::endl;
  std::cout << "C.position() = " << C.position() << std::endl;
  std::cout << "D.position() = " << D.position() << std::endl;

  // Testing movePrev()
  std::cout << "B: ";
  for (i = 1; i <= 7; i++) {
    std::cout << B.movePrev() << " ";
  }
  std::cout << std::endl << "B.position() = " << B.position() << std::endl;

  // Testing moveNext()
  std::cout << "C: ";
  for (i = 1; i <= 7; i++) {
    std::cout << C.moveNext() << " ";
  }
  std::cout << std::endl << "C.position() = " << C.position() << std::endl;

  // Testing findNext() and findPrev()
  std::cout << B.findNext(5) << std::endl;
  B.eraseBefore();
  B.eraseAfter();
  std::cout << B.findPrev(2) << std::endl;
  B.eraseBefore();
  B.eraseAfter();
  std::cout << B.findNext(20) << std::endl;
  std::cout << B.findPrev(20) << std::endl;

  // Testing clear()
  A.clear();
  std::cout << "A.length() = " << A.length() << std::endl;

  // Testing equals() and concat()
  cout << "Testing equals() and concat()..." << endl;

  cout << "G = " << G << endl;
  cout << "G.length() = " << G.length() << endl;
  cout << "G.front() = " << G.front() << endl;
  cout << "G.back() = " << G.back() << endl;
  cout << "G.position() = " << G.position() << endl;

  cout << "H = " << H << endl;
  cout << "H.length() = " << H.length() << endl;
  cout << "H.front() = " << H.front() << endl;
  cout << "H.back() = " << H.back() << endl;
  cout << "H.position() = " << H.position() << endl;

  cout << "G == H is " << (G == H ? "true" : "false") << endl;

  I = G.concat(H);
  cout << "I = " << I << endl;
  cout << "I.length() = " << I.length() << endl;
  cout << "I.front() = " << I.front() << endl;
  cout << "I.back() = " << I.back() << endl;
  cout << "I.position() = " << I.position() << endl;

  cout << "G == I is " << (G == I ? "true" : "false") << endl;
  cout << "I == H is " << (I == H ? "true" : "false") << endl;
  A.moveFront();
  try {
    A.peekPrev();
  } catch (std::range_error & e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.movePrev();
  } catch (std::range_error & e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.setBefore(5);
  } catch (std::range_error & e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.eraseBefore();
  } catch (std::range_error & e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  A.moveBack();
  try {
    A.peekNext();
  } catch (std::range_error & e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.moveNext();
  } catch (std::range_error & e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.setAfter(5);
  } catch (std::range_error & e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.eraseAfter();
  } catch (std::range_error & e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  A.clear();
  try {
    A.front();
  } catch (std::length_error & e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.back();
  } catch (std::length_error & e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  cout << endl;

  return 0;
}