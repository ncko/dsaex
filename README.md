## Learned
Use `list->count` to keep track of the number of elements instead of checking `list->first` or list->last` because even if you free `list->first` and reassign it, you may not end up reassigning `list->last` which is necessary if the list is down to one element.

Easier to just use `list->count`
