/////////////////////////////////////////////////////////////////////
// DirExplorerI.cpp - Template directory explorer                  //
// ver 1.2                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
/////////////////////////////////////////////////////////////////////

#ifdef TEST_DIREXPLORERI  // only compile the following when defined

#include "DirExplorerI.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/CodeUtilities/CodeUtilities.h"
#include <iostream>

using namespace Utilities;
using namespace FileSystem;

class DerivedDirExplorerI : public DirExplorerI
{
public:
  DerivedDirExplorerI(const std::string& path) : DirExplorerI(path) 
  {
    std::cout << "\n  constructing DerivedDirExplorerI";
  }
  //----< file processing modified for application >-----------------

  virtual void doFile(const std::string& filename)
  {
    if (!done() || showAllInCurrDir())
    {
      std::cout << "\n  derivedFile -->    " << filename;
      ++fileCount_;
    }
  }
  //----< dir processing modified for application >------------------

  virtual void doDir(const std::string& dirname)
  {
    std::cout << "\n  derivedDir --->  " << dirname;
    ++dirCount_;
  }
};

ProcessCmdLine::Usage customUsage()
{
  std::string usage;
  usage += "\n  Command Line: path [/option]* [/pattern]*";
  usage += "\n    path is relative or absolute path where processing begins";
  usage += "\n    [/option]* are one or more options of the form:";
  usage += "\n      /s - walk directory recursively";
  usage += "\n      /h - hide empty directories";
  usage += "\n      /a - on stopping, show all files in current directory";
  usage += "\n    [pattern]* are one or more pattern strings of the form:";
  usage += "\n      *.h *.cpp *.cs *.txt or *.*";
  usage += "\n";
  return usage;
}

int main(int argc, char *argv[])
{
  Title("Demonstrate DirExplorer-Inheritance, " + DirExplorerI::version());

  ProcessCmdLine pcl(argc, argv);
  pcl.usage(customUsage());

  preface("Command Line: ");
  pcl.showCmdLine();
  putline();

  if (pcl.parseError())
  {
    pcl.usage();
    std::cout << "\n\n";
    return 1;
  }

  DerivedDirExplorerI de(pcl.path());
  putline();

  for (auto patt : pcl.patterns())
  {
    de.addPattern(patt);
  }

  if (pcl.hasOption('s'))
  {
    de.recurse();
  }

  if (pcl.hasOption('h'))
  {
    de.hideEmptyDirectories(true);
  }

  if (pcl.hasOption('a'))
  {
    de.showAllInCurrDir(true);
  }

  if (pcl.maxItems() > 0)
  {
    de.maxItems(pcl.maxItems());
  }

  de.search();
  de.showStats();

  std::cout << "\n\n";
  return 0;
}

#endif
