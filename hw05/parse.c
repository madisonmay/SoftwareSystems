/* about glib
a) Where is GLib from and why does it exist?  
      - Originally part of the gtk library
      - Developers took code not specific to the GUI and put it in glib
   Who uses it, and for what?  
      - General purpose library for data structures and threading
   Would it have been better if they had given it a name less likely to be confused with glibc?
      - Yes
b) What are the most important pros and cons of using GLib, as opposed to another library, or just using core C features?
      - Glib is pretty standard and uses an interface similar to the boost libraries for C++, 
c) What do you have to do to compile and run a "Hello GLib" example?
      - Include a valid Makefile using pkg-config

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>

void print_hash(GHashTable *hash) {
  GHashTableIter iter;
  gpointer hash_key, hash_value;

  g_hash_table_iter_init (&iter, hash);
  while (g_hash_table_iter_next (&iter, &hash_key, &hash_value)) {
      printf("%s: %d\n", (gchar *) hash_key, *(gint *) hash_value);
  }
}

gchar *read_file(gchar *file_name) {
  GError *err = NULL;
  gchar *contents;
  // file contents --> gchar *
  gboolean success = g_file_get_contents(file_name, &contents, NULL, &err);

  if (!success) {
      /* Report error to user, and free error */
      fprintf(stderr, "Unable to read file: %s\n", err->message);
      g_error_free(err);
      exit(1);
  }
  return contents;
}

gchar **tokenize(gchar *contents) {
  // split a sting into words
  const char* seperators = ".?!,:;-\"\'/()\n\t\r "; // word breaks
  return g_strsplit_set((const char *) contents, seperators, 0);
}

GHashTable *word_counter(gchar **tokens) {
  // creates a word histogram stored in a GHashTable
  
  gint *value;
  GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);

  while (*tokens != NULL) {
    value = (int *) g_hash_table_lookup(hash, (gpointer) *tokens);
    if (value == NULL) {
      value = malloc(sizeof(int *));
      *value = 0;
    }
    *value += 1;
    g_hash_table_insert(hash, (gpointer) *tokens, (gpointer) value);
    tokens++;
  }
  return hash;
}


int main(int argc, char** argv) {
    gchar *file_name = (gchar *) "alice.txt";
    gchar *contents;

    contents = read_file(file_name);

    // lowercase string
    contents = g_ascii_strdown(contents, -1);

    // split into words
    gchar **tokens = tokenize(contents);

    // count word occurrences
    GHashTable *counter = word_counter(tokens); 

    print_hash(counter);

    // clean up
    g_hash_table_destroy(counter);
}