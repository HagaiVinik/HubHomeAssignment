# The solar system's first inter-planetary jukebox

To test your skills, we are enlisting you to help us in building the worlds first
inter-planetary jukebox.

Astronauts on the International Space Station have a problem: during long stays
aboard the station, they are losing touch with pop-culture. They come back home completely
out of touch with what is cool! This is something we can't live with at Hub, so we
are using our skills to design a jukebox, to which anyone down on Earth can upload
their music.

However, even the most open minded of us have rules about what we do, and don't
like to listen to. The astronauts need some way to control what gets played according
to their preferences. Luckily, we have a lot of experience designing rule engines
to protect virtual & physical assets, so we are adapting our technology to protect
the ears of Earth's astronauts.
___

### Rules

We can define a "rule configuration" as a binary tree, where each node is either
a "test" with two child nodes, or a "terminal" node - `Play` or `Skip`.

To evaluate a song against a rule configuration, we start at the root of the
tree and move from test to test until we reach a terminal node.

If a test node evaluates as `true` we move to it's left child, if `false` we move
to the right child.

A test node is a combination of a *type* and a *parameter*.

These are the types of tests currently supported:
- `Length` - Checks if the song's length is less than or equal to a _value.
- `BPM` - Checks if the song's tempo is less than or equal to a _value.
- `Genre` - Checks whether the song is in a list of genres.
- `ARTIST` - Checks whether the song's artist is in a list of artists.

For example, a test node can be a `BPM` *type* with a *parameter* of `120`. This means that
any song evaluated against this node with a BPM less than or equal to `120`
will move to the left child node, otherwise it will move to the right child node.


An example of a rule tree might be:
```
        Genre
       /     \
      /       \
    BPM        \
    / \        Length
   /   \        /   \
 Play  Skip   Play  Skip
```
Depending on the parameters provided to each of the tests, this rule tree might
describe a configuration where any jazz or country song can play, as long as it is not too fast,
or anything other than jazz or country can play as long as it isn't too long.

Each node in the tree can be given an index `n`, starting from `1`, where a node's
children are indexed as `n * 2` for the left branch, and `n * 2 + 1` for the right.
e.g.
```
        1
      /   \
     /     \
    2       \
   / \       3
  /   \     / \
 4     5   6   7
```

In order to serialize a tree for storage, the nodes are saved in a flat list, where
each node is prefixed by it's index as a `uint32_t`.

To serialize each node it's type is written as a null-terminated `utf-8` string,
followed by it's parameter.
___

#### Integer nodes
For the `BPM` and `Length` nodes, a `uint32_t` parameter is used to describe
how the node should be evaluated.

#### List nodes
For the `ARTIST` and `Genre` rules, the parameter is encoded as a list of null-terminated
`utf-8` strings, prefixed by the number of items in the list as a `uint32_t`.


#### Terminal nodes
Terminal nodes, `Play` and `Skip`, do not have any parameters

___
Here is the above example in serialized form, in hexadecimal
```
➜ xxd example
00000000: 0100 0000 4765 6e72 6500 0200 0000 4a61  ....Genre.....Ja
00000010: 7a7a 0043 6f75 6e74 7279 0002 0000 0042  zz.Country.....B
00000020: 504d 0078 0000 0003 0000 004c 656e 6774  PM.x.......Lengt
00000030: 6800 b400 0000 0400 0000 506c 6179 0005  h.........Play..
00000040: 0000 0053 6b69 7000 0600 0000 506c 6179  ...Skip.....Play
00000050: 0007 0000 0053 6b69 7000                 .....Skip.
```

Where the first index is a `Genre` type with a list of genres of length `2`:
```
|   1   | |    Genre   | |   2   | |   Jazz   ||    Country    |
0100 0000 4765 6e72 6500 0200 0000 4a61 7a7a 0043 6f75 6e74 7200
```

The second index is a `BPM` type with a parameter of `120`:
```
|   2   | |  BPM  | |  120  |
0200 0000 4250 4d00 7800 0000
```

The seventh index is a `Skip` node
```
|   7   | |   Skip   |
0700 0000 536b 6970 00
```

_You can assume that all of the provided trees are complete, and always evaluate
to a terminal state._

___

### Data Integrity

In the extreme conditions of space, unprotected by Earth's atmosphere, cosmic rays
are a problem for data storage. They can easily flip bits causing corruption of
data.

To combat this, we can store data with a cyclic redundancy check (CRC). This is
an error detection code that will allow us to see if any accidental changes to
the data have occurred. The specific algorithm we will use is CRC-32 defined in
the ISO 3309 standard.

When we run CRC-32 on a rule configuration it will produce a 32bit code. We prepend
this to the beginning of our configuration files.

That means the first 4 bytes of every configuration file will contain a CRC of
the rest of the data in the file.

___

### Your task
Your task is to write a program that can parse a rule configuration,
then evaluate a list of songs to determine which of them will be allowed to play,
according to the rules.

If any configuration has been corrupted a warning should be presented to the user
of the program.

You are provided some test configurations which all include a CRC, and a JSON list
of song metadatas with which to test your program.

Please code your solution using `c++`. Feel free to use any third party libraries
that will help you to complete your solution.

This task should not take more than 8 hours.

When you have completed your solution, please submit your source code to us for
review, along with any instructions required to compile and run it.
