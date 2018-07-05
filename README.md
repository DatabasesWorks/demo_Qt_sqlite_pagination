# Sqlite pagination demo (Qt)

How to do efficient pagination in SQLite.
A naive approach would be to just retrieve all records and throw the previous "pages" aways.
A better approach is to use a "smart" query with ordering, and ignore some records that match certain criteria. 
