import sys

if len(sys.argv) < 3:
    print ("Usage :", sys.argv[0], "<vertex file> <edge file>")
    sys.exit()

################################################################################
#                              READING DATA                                    #
################################################################################
vertex_file = open(sys.argv[1])
edge_file = open(sys.argv[2])

# Reading the vertex file
vertex={}
for line in vertex_file:
    words = line.split()
    v_name = words[0]
    v_x = int(words[1])
    v_y = int(words[2])
    vertex[v_name]=[v_x, v_y]

# Reading the edge file
tuples = []
for line in edge_file:
    words = line.split()
    v1 = words[0]
    v2 = words[1]
    tuples += [[v1, v2]]

################################################################################
#                            PRODUCING TEX FILE                                #
################################################################################

# Printing header
print ("\\begin{tikzpicture}")

size = 3

for entry in vertex:
    print ("\draw [fill=violet] (", vertex[entry][0] - size/2,",", end=" ")
    print (vertex[entry][1] - size/2,")", end=" ")
    print ("rectangle (", vertex[entry][0] + size/2,",", end=" ")
    print (vertex[entry][1] + size /2,");")

    #print (entry, vertex[entry])

for entry in tuples:
    source = vertex[entry[0]]
    dest = vertex[entry[1]]
    print("\draw [ultra thick, violet] (", source[0],',', source[1],")", end="")
    print(" -- (",dest[0],',',dest[1],");");

print ("\\end{tikzpicture}")
