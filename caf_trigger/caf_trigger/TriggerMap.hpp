/* File TriggerMap.hpp
 *
 * Created       : June 30, 2006
 * Author        : Jovan Mitrevski
 *
 * Last modified : July 26, 2006
 * Comments      : A little utility to tell you the trigger version
 *                 of a run based on an input runvtriglist.txt.
 *                
 * History       : Was called TopTriggerMap in top_cafe before.
 *
 */



#ifndef TriggerMap_HPP_
#define TriggerMap_HPP_

#include <map>

//namespace caf_trigger {
  
  class TriggerMap{
  public:
    
    // Constructor, destructor: 
    TriggerMap() {BuildMap("caf_trigger/parameters/runvstriglistX100.txt");};
    TriggerMap(char *filename) {BuildMap(filename);};
    ~TriggerMap() {};
    int TriggerX100(int runnum) const  ;
    float TriggerVersion(int runnum) const ; 
    int LastRun() const {return _lastrun;}

  private:

    void BuildMap(char *filename);

    std::map<int, int> _runtrigmap;
   
    int _lastrun;

  }; // class TriggerMap{
  
//} // namespace caf_trigger {

#endif
