#include "searcher.h"

namespace kiwix {

  /* Constructor */
  Searcher::Searcher(const string &xapianDirectoryPath) 
    : stemmer(Xapian::Stem("english")) {
    this->openDatabase(xapianDirectoryPath);
  }
  
  /* Destructor */
  Searcher::~Searcher() {
  }

  /* Open Xapian readable database */
  void Searcher::openDatabase(const string &directoryPath) {
    this->readableDatabase = Xapian::Database(directoryPath);
  }
  
  /* Close Xapian writable database */
  void Searcher::closeDatabase() {
    return;
  }
  
  /* Search strings in the database */
  void Searcher::search(const string &search, const unsigned int resultsCount) {
    /* Reset the results */
    this->results.clear();
    this->resultOffset = this->results.begin();
    
    /* Create the enquire object */
    Xapian::Enquire enquire(this->readableDatabase);
    
    /* Create the query term vector */
    std::vector<std::string> queryTerms = split(removeAccents(search.c_str()), " #@%$0/\\_-*()[]{},;:");
    
    /* Create query object */
    Xapian::Query query(Xapian::Query::OP_OR, queryTerms.begin(), queryTerms.end());
    
    /* Set the query in the enquire object */
    enquire.set_query(query);
    
    cout << "Performing query `" <<
      query.get_description() << "'" << endl;
    
    /* Get the results */
    Xapian::MSet matches = enquire.get_mset(0, resultsCount);
    
    Xapian::MSetIterator i;
    for (i = matches.begin(); i != matches.end(); ++i) {
      Xapian::Document doc = i.get_document();
      
      Result result;
      result.url = doc.get_data();
      result.title = doc.get_value(0);
      result.score = i.get_percent();
      
      this->results.push_back(result);
      
      cout << "Document ID " << *i << "   \t";
      cout << i.get_percent() << "% ";
      cout << "\t[" << doc.get_data() << "] - " << doc.get_value(0) << endl;
    }
    
    /* Set the cursor to the begining */
    this->resultOffset = this->results.begin();

    return;
  }
  
  /* Reset the results */
  void Searcher::reset() {
    this->results.clear();
    this->resultOffset = this->results.begin();
    return;
  }
  
  /* Get next result */
  bool Searcher::getNextResult(string &url, string &title, unsigned int &score) {
    bool retVal = false;
    
    if (this->resultOffset != this->results.end()) {
      
      /* url */
      url = this->resultOffset->url;
      
      /* title */
      title = this->resultOffset->title;
      
      /* score */
      score =  this->resultOffset->score;
      
      /* increment the cursor for the next call */
      this->resultOffset++;
      
      retVal = true;
    }

    return retVal;
  }
  
}
