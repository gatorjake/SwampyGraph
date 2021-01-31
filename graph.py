#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import dash
import dash_core_components as dcc
import dash_html_components as html
import networkx as nx
import plotly.graph_objs as go

import pandas as pd
from colour import Color
from datetime import datetime
from textwrap import dedent as d
import json
import base64
import datetime
import io
import dash_table
from ctypes import *
actualclicks=0
actualclicks2=0
actualclicks3=0
ab1=[]
ab2=[]
def load_snakey_lib():
    lib = cdll.LoadLibrary("./libuntitled3.so")
    lib.swamp.restype = None
    lib.swamp.argtypes = [c_char_p, c_char_p, c_char_p, c_char_p, c_char_p]
    return lib
def libStuff(msg, msg2):
    print(1000000)
    print(msg)
    print(msg2)
    lib=load_snakey_lib()
    msg3=bytes(msg, 'utf-8')
    buf=create_string_buffer(100000000)
    msg4=bytes(msg2, 'utf-8')
    lib.swamp(msg3,msg4,bytes(confounderA, 'utf-8'),bytes(confounderB,'utf-8'),buf)
    print(buf.value.decode('cp437'))
    return buf.value.decode('cp437')
printit=False
confounderA=''
confounderB=''
print(10)
def bfs(source, destination):
    print("100000000000000000000000000000")
    count=0
    arr=[]
    for i in list(G.nodes):
        if list(G.nodes)[count]==source:
            break
        count+=1
    queue=[]
    visited=[]
    queue.append(source)
    visited.append(source)
    while(len(queue)>0):
        top=queue.pop()
        print(top)
        print(dict2[top])
        for i in dict2[top]:
            if i not in visited:
                arr.append([top,i, True])
                visited.append(i)
                queue.append(i)
                if i==destination:
                    print(arr, "ARR")
                    return arr
            else:
                arr.append([top,i, False])
    print(arr)
    return arr

# import the css template, and pass the css template into dash
external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']
app = dash.Dash(__name__, external_stylesheets=external_stylesheets)
app.title = "Confounder Finder"
y=0
realValAt=0
YEAR=[2010, 2019]
ACCOUNT="A0001"
G=nx.Graph()
G.add_node('1')
G.add_node('2')
G.add_node('3')
G.add_node("Hello")
G.add_node("yolo")
G.add_node("haha")
edgeWeights=[]
for i in list(G.nodes):
    for k in list(G.nodes):
        G.add_edge(i,k)
        edgeWeights.append(1)
nx.drawing.layout.spring_layout(G)
print((list(G.nodes)))
newEdgeName=''
newVertexName=''
newEdgeWeight=0
newEdgeDir=False
newEdgeVertexAName=''
newEdgeVertexBName=''
array=[]
dict2={}
source=''
target=''
option=''
for i in list(G.edges):
    abcd=i[0]
    abce=i[1]
    if not abcd in dict2:
        dict2[abcd]=[]
    dict2[abcd].append(abce)

print(dict2)
##############################################################################################################################################################
def network_graph(yearRange, AccountToSearch):
    global array
    print(array)
    print(list(G.nodes))
    print(list(G.edges))
 #   edgelist = pd.read_csv('C:\\Users\\Andrew\\PycharmProjects\\stuff\\venv\\Scripts\\edge1.csv')
#    nodelist = pd.read_csv('C:\\Users\\Andrew\\PycharmProjects\\stuff\\venv\\Scripts\\node1.csv')

    global newEdgeVertexAName
    global edgeWeights
    global newEdgeVertexBName
    global newVertexName
    global newEdgeDir
    global newEdgeWeight
    global newEdgeName
    global realValAt
    global dict
    global y
    global target
    global source
    global option
    print("B: ",newEdgeVertexBName)
    print("A: ",newEdgeVertexAName)
    if(newVertexName!=''):
        G.add_node(newVertexName)
        newVertexName=''
    if(newEdgeVertexAName!='' and newEdgeVertexBName!=''):
        count=0
        aindex=-1
        bindex=-1
        arrr=list(G.nodes)
        for i in arrr:
            if arrr[count]==newEdgeVertexAName:
                aindex=count
            if arrr[count]==newEdgeVertexBName:
                bindex=count
            count+=1
        if aindex!=-1 and bindex!=-1:
            G.add_edge(list(G.nodes)[aindex], list(G.nodes)[bindex])
            edgeWeights.append(newEdgeWeight)
            newEdgeVertexAName=''
            newEdgeVertexBName=''
            newEdgeWeight=0
    print(YEAR)
    print(ACCOUNT)
    print("Hahahahahahah")
    '''
    edges=edge1.to_numpy()
    vertices=node1.to_numpy()
    print(type(edge1))
    print(edge1['Source'])

    # filter the record by datetime, to enable interactive control through the input box
    edge1['Datetime'] = "" # add empty Datetime column to edge1 dataframe
    accountSet=set() # contain unique account
    for index in range(0,len(edge1)):
        edge1['Datetime'][index] = datetime.strptime(edge1['Date'][index], '%d/%m/%Y')
        if edge1['Datetime'][index].year<yearRange[0] or edge1['Datetime'][index].year>yearRange[1]:
            edge1.drop(axis=0, index=index, inplace=True)
            continue
        accountSet.add(edge1['Source'][index])
        accountSet.add(edge1['Target'][index])
    print(accountSet)
    print(edge1)

    '''

    accountSet=set()
    for i in G.nodes:
        accountSet.add(i)

    # to define the centric point of the networkx layout
    shells=[]
    shell1=[]
    shell1.append(AccountToSearch)
    shells.append(shell1)


    shell2=[]
    for ele in accountSet:
        if ele!=AccountToSearch:
            shell2.append(ele)
    shells.append(shell2)
    #print(shells)

    #G = nx.from_pandas_edgelist(edge1, 'Source', 'Target', ['Source', 'Target', 'TransactionAmt', 'Date'], create_using=nx.MultiDiGraph())
    #a={"abc", "123", "abd"}
    #G.add_node(a)
    #nx.set_node_attributes(G, node1.set_index('Account')['CustomerName'].to_dict(), 'CustomerName')
    #nx.set_node_attributes(G, node1.set_index('Account')['Type'].to_dict(), 'Type')
    # pos = nx.layout.spring_layout(G)
    # pos = nx.layout.circular_layout(G)
    # nx.layout.shell_layout only works for more than 3 nodes
    print(10)
    #arr=G.nodes.to_numpy()
    #print(arr)
    #print(vertices[0])
    #nx.Graph.add_edge(G,vertices[0], vertices[1])
    #nx.Graph.add_edge()
    if len(shell2)>1:
        pos = nx.drawing.layout.shell_layout(G, shells)
    else:
        pos = nx.drawing.layout.spring_layout(G)
    for node in G.nodes:
        G.nodes[node]['pos'] = list(pos[node])


    if len(shell2)==0:
        traceRecode = []  # contains edge_trace, node_trace, middle_node_trace

        node_trace = go.Scatter(x=tuple([1]), y=tuple([1]), text=tuple([str(AccountToSearch)]), textposition="bottom center",
                                mode='markers+text',
                                marker={'size': 50, 'color': 'LightSkyBlue'})
        traceRecode.append(node_trace)

        node_trace1 = go.Scatter(x=tuple([1]), y=tuple([1]),
                                mode='markers',
                                marker={'size': 50, 'color': 'LightSkyBlue'},
                                opacity=0)
        traceRecode.append(node_trace1)
        figure = {
            "data": traceRecode,
            "layout": go.Layout(title='Confounding Graph', showlegend=False,
                                margin={'b': 40, 'l': 40, 'r': 40, 't': 40},
                                xaxis={'showgrid': False, 'zeroline': False, 'showticklabels': False},
                                yaxis={'showgrid': False, 'zeroline': False, 'showticklabels': False},
                                height=600
                                )}
        return figure

    traceRecode = []  # contains edge_trace, node_trace, middle_node_trace
    ############################################################################################################################################################
    colors = list(Color('lightcoral').range_to(Color('darkred'), len(G.edges())))
    colors = ['rgb' + str(x.rgb) for x in colors]

    colorArr=[]
    index = 0
    print(array, len(array), "right on dude", realValAt)
    print(G.edges)
    if len(array)!=0:
        print("okay here we go")
        for edge in list(G.edges):
            t=False
            for i in range(0, realValAt):
                if array[i][0]==edge[0] and array[i][1]==edge[1] and array[i][2]==True:
                    colorArr.append('rgb(59, 227, 98)')
                    t=True
            if array[realValAt][0]==edge[0] and array[realValAt][1]==edge[1] and array[realValAt][2]==True:
                colorArr.append('rgb(59, 227, 98)')
                t=True
            if array[realValAt][0]==edge[0] and array[realValAt][1]==edge[1] and array[realValAt][2]==False:
                colorArr.append('rgb(189, 17, 17)')
                t=True
            if not t:
                colorArr.append('rgb(0,0,0)')

    if len(array)==0:

        for edge in G.edges:
            x0, y0 = G.nodes[edge[0]]['pos']
            x1, y1 = G.nodes[edge[1]]['pos']
            weight = edgeWeights[index]#float(G.edges[edge]['TransactionAmt']) / max(edge1['TransactionAmt']) * 10
            trace = go.Scatter(x=tuple([x0, x1, None]), y=tuple([y0, y1, None]),
                               mode='lines',
                               line={'width': weight},
                               marker=dict(color=colors[index]),
                               line_shape='spline',
                               opacity=1)
            traceRecode.append(trace)
            index = index + 1
    else:
        print (G.edges)
        for edge in G.edges:
            x0, y0 = G.nodes[edge[0]]['pos']
            x1, y1 = G.nodes[edge[1]]['pos']
            weight = edgeWeights[
                index]  # float(G.edges[edge]['TransactionAmt']) / max(edge1['TransactionAmt']) * 10
            trace = go.Scatter(x=tuple([x0, x1, None]), y=tuple([y0, y1, None]),
                               mode='lines',
                               line={'width': weight},
                               marker=dict(color=colorArr[index]),
                               line_shape='spline',
                               opacity=1)
            traceRecode.append(trace)
            index = index + 1
    ###############################################################################################################################################################
    node_trace = go.Scatter(x=[], y=[], hovertext=[], text=[], mode='markers+text', textposition="bottom center",
                            hoverinfo="text", marker={'size': 50, 'color': 'LightSkyBlue'})

    index = 0
    for node in G.nodes():
        x, y = G.nodes[node]['pos']
        print(list(G.nodes())[index])
        hovertext = "hi"+"<br>"#+str(#"CustomerName: " + str(G.nodes[node]['CustomerName']) + "<br>" + "AccountType: " + str(
            #G.nodes[node]['Ty])
        text = list(G.nodes())[index]#node1['Account'][index]
        node_trace['x'] += tuple([x])
        node_trace['y'] += tuple([y])
        node_trace['hovertext'] += tuple([hovertext])
        node_trace['text'] += tuple([text])
        index = index + 1

    traceRecode.append(node_trace)
    ################################################################################################################################################################
    middle_hover_trace = go.Scatter(x=[], y=[], hovertext=[], mode='markers', hoverinfo="text",
                                    marker={'size': 20, 'color': 'LightSkyBlue'},
                                    opacity=0)
    index = 0
    for edge in G.edges:
        x0, y0 = G.nodes[edge[0]]['pos']
        x1, y1 = G.nodes[edge[1]]['pos']
        hovertext = "From: " #+ str(G.edges[edge]['Source']) + "<br>" + "To: " #+ #str(
          #  G.edges[edge]['Target']) + "<br>" + "TransactionAmt: " #+ str(
           # G.edges[edge]['TransactionAmt']
       # ) + "<br>" #+"TransactionDate: " + str(G.edges[edge]['Date'])
        middle_hover_trace['x'] += tuple([(x0 + x1) / 2])
        middle_hover_trace['y'] += tuple([(y0 + y1) / 2])
        middle_hover_trace['hovertext'] += tuple([hovertext])
        index = index + 1

    traceRecode.append(middle_hover_trace)
    #################################################################################################################################################################
    figure = {
        "data": traceRecode,
        "layout": go.Layout(title='Interactive Transaction Visualization', showlegend=False, hovermode='closest',
                            margin={'b': 40, 'l': 40, 'r': 40, 't': 40},
                            xaxis={'showgrid': False, 'zeroline': False, 'showticklabels': False},
                            yaxis={'showgrid': False, 'zeroline': False, 'showticklabels': False},
                            height=600,
                            clickmode='event+select',
                            annotations=[
                                dict(
                                    ax=(G.nodes[edge[0]]['pos'][0] + G.nodes[edge[1]]['pos'][0]) / 2,
                                    ay=(G.nodes[edge[0]]['pos'][1] + G.nodes[edge[1]]['pos'][1]) / 2, axref='x', ayref='y',
                                    x=(G.nodes[edge[1]]['pos'][0] * 3 + G.nodes[edge[0]]['pos'][0]) / 4,
                                    y=(G.nodes[edge[1]]['pos'][1] * 3 + G.nodes[edge[0]]['pos'][1]) / 4, xref='x', yref='y',
                                    showarrow=True,
                                    arrowhead=3,
                                    arrowsize=4,
                                    arrowwidth=1,
                                    opacity=1
                                ) for edge in G.edges]
                            )}
    return figure
######################################################################################################################################################################
#
#styles: for right side hover/click component
styles = {
    'pre': {
        'border': 'thin lightgrey solid',
        'overflowX': 'scroll'
    }
}
app.layout = html.Div([
    #########################Title
    html.Div([html.H1("Confounders Graph")],
             className="row",
             style={'textAlign': "center"}),
    #############################################################################################define the row
    html.Div(
        className="row",
        children=[
            ##############################################left side two input components

html.Div([
    dcc.Dropdown(
        id='demo-dropdown2',
        options=[
            {'label': 'BFS', 'value': 'BFS'}
        ],
        value='BFS'
    ),
    html.Div(id='dd-output-container2',children='choose option')
]),
html.Div([
    dcc.Textarea(
        id='text5',
        value='',
        style={'width': '100%', 'height': 50},
        placeholder='source',
    ),
    html.Div(id='textarea-example-output5', style={'whiteSpace': 'pre-line'})
]),
html.Div([
    dcc.Textarea(
        id='text6',
        value='',
        style={'width': '100%', 'height': 50},
        placeholder='sink',
    ),
    html.Div(id='textarea-example-output6', style={'whiteSpace': 'pre-line'})
]),

html.Div([
    dcc.Textarea(
        id='text7',
        value='',
        style={'width': '100%', 'height': 50},
        placeholder='exposure',
    ),
    html.Div(id='textarea-example-output7', style={'whiteSpace': 'pre-line'})
]),
html.Div([
    dcc.Textarea(
        id='text8',
        value='',
        style={'width': '100%', 'height': 50},
        placeholder='outcome',
    ),
    html.Div(id='textarea-example-output8', style={'whiteSpace': 'pre-line'})
]),html.Div(children=[html.Button('Submit', id='submit-val', n_clicks=0),html.Div(id='sVal')]),
            html.Div(
                className="two columns",
                children=[
                    dcc.Markdown(d("""
                            **Time Range To Visualize**

                            Slide the bar to define year range.
                            """)),
                    html.Div(
                        className="twelve columns",
                        children=[
                            dcc.Slider(
                                id='my-range-slider',
                                min=0,
                                max=len(array)-1,
                                step=1,
                                value=0
                            ),
                            html.Br(),
                            html.Div(id='output-container-range-slider')
                        ],
                        style={'height': '300px'}
                    ),

                ]
            ),

            ############################################middle graph component
            html.Div(
                className="eight columns",
                children=[dcc.Graph(id="my-graph",
                                    figure=network_graph(YEAR, ACCOUNT)),
                          dcc.Interval(id='auto-stepper',
                                       interval=1 * 1000,  # in milliseconds
                                       n_intervals=0
                                       ),
                          dcc.Slider(
                              id="steper",
                              min=0,
                              max=4,
                              value=0
                          ),
html.Div(id='s1')]
            ),

            #########################################right side two output component
            html.Div(
                className="two columns",
                children=[
                    html.Div(
                        className='twelve columns',
                        children=[
                            dcc.Markdown(d("""
                            **Hover Data**

                            Mouse over values in the graph.
                            """)),
                            html.Pre(id='hover-data', style=styles['pre'])
                        ],
                        style={'height': '400px'}),

                    html.Div(
                        className='twelve columns',
                        children=[
                            dcc.Markdown(d("""
                            **Click Data**

                            Click on points in the graph.
                            """)),
                            html.Pre(id='click-data', style=styles['pre'])
                        ],
                        style={'height': '400px'})
                ]



    ),
html.Div([
    dcc.Textarea(
        id='vertexTextID',
        value='',
        style={'width': '100%', 'height': 50},
        placeholder='vertex name'
    ),
    html.Div(id='vertexText', style={'whiteSpace': 'pre-line'})
]),

html.Div([
    dcc.Dropdown(
        id='demo-dropdown',
        options=[
            {'label': 'Undirected', 'value': 'Undirected'},
            {'label': 'Directed', 'value': 'Directed'},
        ],
        value='Undirected'
    ),
    html.Div(id='dd-output-container',children='choose option')
]),
html.Div([
    dcc.Textarea(
        id='text1',
        value='',
        style={'width': '100%', 'height': 50},
        placeholder='firstVertex'
    ),
    html.Div(id='textarea-example-output1', style={'whiteSpace': 'pre-line'})
]),

html.Div([
    dcc.Textarea(
        id='text2',
        value='',
        style={'width': '100%', 'height': 50},
        placeholder='secondVertex'
    ),
    html.Div(id='textarea-example-output2', style={'whiteSpace': 'pre-line'})
]),

html.Div([
    dcc.Textarea(
        id='text3',
        value='0',
        style={'width': '100%', 'height': 50},
        placeholder='weight',
    ),
    html.Div(id='textarea-example-output3', style={'whiteSpace': 'pre-line'})
]),

html.Div([
    dcc.Upload(
        id='upload-data',
        children=html.Div([
            'Drag and Drop Vertex File or ',
            html.A('Select Files')
        ]),
        style={
            'width': '100%',
            'height': '60px',
            'lineHeight': '60px',
            'borderWidth': '1px',
            'borderStyle': 'dashed',
            'borderRadius': '5px',
            'textAlign': 'center',
            'margin': '10px'
        },
        # Allow multiple files to be uploaded
        multiple=True
    ),
    html.Div(id='output-data-upload'),
]),

           html.Div([
    dcc.Upload(
        id='upload-data2',
        children=html.Div([
            'Drag and Drop Edge File or ',
            html.A('Select Files')
        ]),
        style={
            'width': '100%',
            'height': '60px',
            'lineHeight': '60px',
            'borderWidth': '1px',
            'borderStyle': 'dashed',
            'borderRadius': '5px',
            'textAlign': 'center',
            'margin': '10px'
        },
        # Allow multiple files to be uploaded
        multiple=True
    ),
    html.Div(id='output-data-upload2'),
])

])])


###################################callback for left side components


def parse_contents(contents, filename, date):
    content_type, content_string = contents.split(',')

    decoded = base64.b64decode(content_string)
    try:
        if 'csv' in filename:
            # Assume that the user uploaded a CSV file
            df = pd.read_csv(
                io.StringIO(decoded.decode('utf-8')))
        elif 'xls' in filename:
            # Assume that the user uploaded an excel file
            df = pd.read_excel(io.BytesIO(decoded))
    except Exception as e:
        print(e)
        return html.Div([
            'There was an error processing this file.'
        ])

    return df['vertex']


@app.callback(dash.dependencies.Output('output-data-upload', 'children'),
              dash.dependencies.Input('upload-data', 'contents'),
              dash.dependencies.State('upload-data', 'filename'),
              dash.dependencies.State('upload-data', 'last_modified'))
def update_output(list_of_contents, list_of_names, list_of_dates):
    if list_of_contents is not None:
        ab1= [parse_contents(c, n, d) for c, n, d in
            zip(list_of_contents, list_of_names, list_of_dates)]
        print(ab1)
        for i in ab1:
            print(ab1)
        return ab1



@app.callback(dash.dependencies.Output('output-data-upload2', 'children'),
              dash.dependencies.Input('upload-data2', 'contents'),
              dash.dependencies.State('upload-data2', 'filename'),
              dash.dependencies.State('upload-data2', 'last_modified'))
def update_output(list_of_contents, list_of_names, list_of_dates):
    if list_of_contents is not None:
        children = [
            parse_contents(c, n, d) for c, n, d in
            zip(list_of_contents, list_of_names, list_of_dates)]
        return children




@app.callback(
    dash.dependencies.Output('my-graph', 'figure'),
    [dash.dependencies.Input('my-range-slider', 'value')],
    [dash.dependencies.Input('submit-val', 'n_clicks')],
    dash.dependencies.Input('upload-data', 'contents'),
    dash.dependencies.State('upload-data', 'filename'),
    dash.dependencies.State('upload-data', 'last_modified'))
def update_output(value, n_clicks,list_of_contents,list_of_names,list_of_dates):
    global actualclicks
    global actualclicks2
    global actualclicks3
    global printit
    global realValAt
    global ab1
    boo=False
    if n_clicks>actualclicks and newEdgeVertexAName !='' and newEdgeVertexBName!='' and newEdgeWeight!=0:
        boo=True
        actualclicks = n_clicks
        G.add_edge(newEdgeVertexAName, newEdgeVertexBName, newEdgeWeight)
        edgeWeights.append(newEdgeWeight)

        return network_graph(YEAR, ACCOUNT)
    if n_clicks>actualclicks and newVertexName!='':
        boo=True
        actualclicks = n_clicks
        G.add_node(newVertexName)
        return network_graph(YEAR, ACCOUNT)
    print(n_clicks)
    print(actualclicks)
    if n_clicks>actualclicks and not boo:
        actualclicks=n_clicks
        stri = '['
        c=0
        for i in list(G.nodes):
            if c != len(list(G.nodes))-1:
                stri += i + ","
            else:
                stri+=i
            c+=1
        stri += "]"

        str2 = '['
        index = 0
        for i in list(G.edges):
            str2 += "[" + (i[0]) + "," + (i[1]) + "," + str(edgeWeights[index]) + "]"
            index += 1
        str2 += "]"
        print(stri)
        libStuff(stri,str2)
        return network_graph(YEAR, ACCOUNT)
    if list_of_contents is not None:
        ab1 = [
            parse_contents(c, n, d) for c, n, d in
            zip(list_of_contents, list_of_names, list_of_dates)]

        return network_graph(YEAR, ACCOUNT)
    realValAt=value
    print("JAskmwimidwimeie")
    return network_graph(YEAR, ACCOUNT)
    # to update the global variable of YEAR and ACCOUNT
################################callback for right side components

def generate_figure():
    return network_graph(YEAR, ACCOUNT)

@app.callback(
    dash.dependencies.Output('hover-data', 'children'),
    [dash.dependencies.Input('my-graph', 'hoverData')])
def display_hover_data(hoverData):
    return json.dumps(hoverData, indent=2)


@app.callback(
    dash.dependencies.Output('click-data', 'children'),
    [dash.dependencies.Input('my-graph', 'clickData')])
def display_click_data(clickData):
    return json.dumps(clickData, indent=2)

'''
@app.callback(
    dash.dependencies.Output('my-graph', 'figure'),
    [dash.dependencies.Input('submit-val', 'n_clicks')],
)
def update_output2(n_clicks):
    if n_clicks>0:
        print(n_clicks)
        G.add_node(n_clicks)
        return generate_figure()
        '''

'''
@app.callback(
    dash.dependencies.Output('submit-value-2', 'figure'),
    [dash.dependencies.Input('submit-val2', 'n_clicks')],
)
def update_output2(n_clicks):
    if n_clicks>0:
        print(n_clicks)
        G.add_node(n_clicks)
        generate_figure()
        return "1"
'''
'''
@app.callback(
    dash.dependencies.Output('s1', 'value'),
    [dash.dependencies.Input('auto-stepper', 'n_intervals')])
def on_click(n_intervals):
    print ("aaaaaaa",n_intervals)
    global y
    if y==0:
        y+=1
        return 0


    if n_intervals is None:
        return 0
    else:
        return (n_intervals+1)%5

        '''

@app.callback(
    dash.dependencies.Output('dd-output-container', 'children'),
    [dash.dependencies.Input('demo-dropdown', 'value')])
def update_output(value):
    global newEdgeDir
    if value=='Undirected':
        newEdgeDir=False
    else:
        newEdgeDir=True
    return ''


@app.callback(
    dash.dependencies.Output('dd-output-container2', 'children'),
    [dash.dependencies.Input('demo-dropdown2', 'value')])
def update_output(value):
    global array
    global option
    global source
    global target
    option=''
    array=[]
    print(source, target)
    if source in list(G.nodes) and target in list(G.nodes):
        array=bfs(source, target)
    option=value
    ma=5
    if array!=[]:
        ma=len(array)-1
    return '',ma

@app.callback(
    dash.dependencies.Output('textarea-example-output1', 'children'),
    [dash.dependencies.Input('text1', 'value')]
)
def update_output(value):
    global newEdgeVertexAName
    newEdgeVertexAName=value
    return ''


@app.callback(
    dash.dependencies.Output('textarea-example-output2', 'children'),
    [dash.dependencies.Input('text2', 'value')]
)
def update_output(value):
    global newEdgeVertexBName
    print(value)
    newEdgeVertexBName=value
    return ''



@app.callback(
    dash.dependencies.Output('vertexText', 'children'),
    [dash.dependencies.Input('vertexTextID', 'value')]
)
def update_output(value):
    global newVertexName
    newVertexName=value
    return ''

@app.callback(
    dash.dependencies.Output('textarea-example-output5', 'children'),
    [dash.dependencies.Input('text5', 'value')]
)
def update_output(value):
    global source
    global option
    global target
    global array
    source=''
    array=[]
    source=value
    if source in list(G.nodes) and target in list(G.nodes) and option!='':
        if option=='BFS':
            array=bfs(source, target)
    ma = 5
    if array != []:
        ma = len(array) - 1
    return '', ma



@app.callback(
    dash.dependencies.Output('textarea-example-output7', 'children'),
    [dash.dependencies.Input('text7', 'value')]
)
def update_output(value):
    global confounderA
    confounderA=value
    return ''


@app.callback(
    dash.dependencies.Output('textarea-example-output8', 'children'),
    [dash.dependencies.Input('text8', 'value')]
)
def update_output(value):
    global confounderB
    confounderB=value
    return ''



@app.callback(
    dash.dependencies.Output('textarea-example-output6', 'children'),
    dash.dependencies.Output('my-range-slider', 'max'),
    [dash.dependencies.Input('text6', 'value')]
)
def update_output(value):
    global source
    global option
    global target
    global array
    target=''
    target=value
    array=[]
    print("value",value)
    print(source, target, "Targeeeeeeeeeeeeet")
    if source in list(G.nodes) and target in list(G.nodes) and option != '':
        if option == 'BFS':
            array=bfs(source, target)

    ma = 5
    print(array)
    if array != []:
        ma = len(array) - 1
    return '', ma


@app.callback(
    dash.dependencies.Output('textarea-example-output3', 'children'),
    [dash.dependencies.Input('text3', 'value')]
)
def update_output(value):
    global newEdgeWeight
    newEdgeWeight=(int)(value)
    return ''



    #return 0;
    #return 'The input value was "{}" and the button has been clicked {} times'.format(
       # value,
        #n_clicks
    #)



if __name__ == '__main__':
    app.run_server(debug=True)



