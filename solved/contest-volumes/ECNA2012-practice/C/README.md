C - You've Got Nothing to Hit but the Heights
=============================================

**Note:** This solution has not been submitted,
so it's not guaranteed to be an "Accepted Answer".

Plan of attack:

We want a list of actors so we can sort them in descending order.
To do so, you'll need an Actor class/struct. Once the list of
actors has been sorted, use a "two finger" scan to find a
potential cast. The first finger points at the potential father,
while the second finger is used to find a potential son and
grandson. We know the required heights, so we first search for a
an actor that matches the height of the son role. Once he's been
found, we search for an actor that matches the height of the
grandson role. If all roles have been filled, we can print the
cast. In either case, we advance the search for a new cast
by moving the first finger to the next potential father.
