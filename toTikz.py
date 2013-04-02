import sys

def usage():
    print ("tikzpicture :", sys.argv[0], "<vertex file> <edge file>")
    print ("standalone :", sys.argv[0], "-s <vertex file> <edge file>");
    sys.exit()

if len(sys.argv) < 3:
    usage();

standalone = 0
if sys.argv[1] == "-s":
    standalone = 1
    if len(sys.argv) < 4:
        usage()
    sys.argv[1] = sys.argv[2]
    sys.argv[2] = sys.argv[3]


################################################################################
#                              READING DATA                                    #
################################################################################
vertex_file = open(sys.argv[1])
edge_file = open(sys.argv[2])

scale = 1.0 / 20

# Reading the vertex file
vertex={}
for line in vertex_file:
    words = line.split()
    v_name = words[0]
    v_x = int(words[1]) * scale
    v_y = int(words[2]) * scale
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
if standalone:
    print ("\\documentclass{article}")
    print ("\\usepackage{tikz}")
    print ("\\begin{document}")
    print ("\\resizebox{\\columnwidth}{!}{")
print ("\\begin{tikzpicture}")
print ("\\tikzstyle{every node}=[font=\\huge]")

size = 0.2
delta = 0.8

# Printing Vertex
for entry in vertex:
    print ("\draw [fill=violet] (", vertex[entry][0] - size/2,",", end=" ")
    print (vertex[entry][1] - size/2,")", end=" ")
    print ("rectangle (", vertex[entry][0] + size/2,",", end=" ")
    print (vertex[entry][1] + size /2,");")
    # Printing name
    print("\\node at (",vertex[entry][0],",",vertex[entry][1] + delta, end="")
    print(") {",entry,"};")

# Printing Edges
for entry in tuples:
    source = vertex[entry[0]]
    dest = vertex[entry[1]]
    print("\draw [ultra thick, violet] (", source[0],',', source[1],")", end="")
    print(" -- (",dest[0],',',dest[1],");");

# Printing foot
print ("\\end{tikzpicture}")
if standalone:
    print ("}")
    print ("\\end{document}")
