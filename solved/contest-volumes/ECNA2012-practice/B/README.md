B - It All Adds Up
==================

**Note:** This solution has not been submitted, so it's not guaranteed to be an "Accepted Answer".

Plan of attack:

Brute force it with some slight optimizations.
Use a "two finger" scan. Don't need to scan the whole range
because there is a threshold where the sum will always exceed
*n*. While the first finger is on the starting point, the second
finger starts sequentially adding the remaining integers
while the sum is still less than *n*. If the sum equals *n*,
a valid partition has been found so we can advance the first
finger. If the counting sum exceeds *n*, we also advance the
first finger.
