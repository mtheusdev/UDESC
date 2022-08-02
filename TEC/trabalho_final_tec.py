def writeRow(list, row):
    list.append('{} {} {} {} {}\n'.format(row[0], row[1], row[2], row[3], row[4]))

def writeInFile(fileName, list):
    with open(fileName, 'w') as file:
        for row in list:
            file.write(row)

def getList():
  translatedRowsList = [
      '0 1 # r ¢1\n',
      '0 0 # r ¢0\n',
      '¢1 1 1 r ¢1\n',
      '¢1 0 1 r ¢0\n',
      '¢1 _ 1 r ¢back\n',
      '¢0 1 0 r ¢1\n',
      '¢0 0 0 r ¢0\n',
      '¢0 _ 0 l ¢back\n',
      '¢back # * r ¢\n',
      '¢back _ ! l ¢back\n',
      '¢back * * l ¢back\n',
      '¢ _ ! l 1\n',
      '¢ 0 0 r ¢\n',
      '¢ 1 1 r ¢\n',
      '¢ B B r ¢\n',
      '¢ X X r ¢\n',
      '¢ # * r ¢¢white\n',
      '¢¢white 1 _ r ¢¢1\n',
      '¢¢white 0 _ r ¢¢0\n',
      '¢¢white _ _ r ¢¢_\n',
      '¢¢white ! _ r ¢¢final\n',
      '¢¢1 1 1 r ¢¢1\n',
      '¢¢1 0 1 r ¢¢0\n',
      '¢¢1 _ 1 r ¢¢white\n',
      '¢¢1 ! 1 r ¢¢final\n',
      '¢¢0 1 0 r ¢¢1\n',
      '¢¢0 0 0 r ¢¢0\n',
      '¢¢0 _ 0 r ¢¢white\n',
      '¢¢0 ! 0 r ¢¢final\n',
      '¢¢_ 1 _ r ¢¢1\n',
      '¢¢_ 0 _ r ¢¢0\n',
      '¢¢_ _ _ r ¢¢white\n',
      '¢¢_ ! _ r ¢¢final\n',
      '¢¢final _ ! l ¢¢back\n',
      '¢¢back # * r ¢\n',
      '¢¢back * * l ¢¢back\n',
      '¢ ! _ r ¢¢finalWhite\n',
      '¢¢finalWhite * ! l ¢\n',
  ]
  return translatedRowsList

def writeRows(translatedRowsList, states):
  for state in states:
        whiteState = '¢' + state + 'white'
        state_1 = '¢' + state + '1'
        state_0 = '¢' + state + '0'
        state_ = '¢' + state + '_'
        backState = '¢' + state + 'back'
        whiteBackState = '¢' + state + 'finalWhite'
        finalState = '¢' + state + 'final'

        writeRow(translatedRowsList, (state, '#', '*', 'r', whiteState))
        writeRow(translatedRowsList, (whiteState, '1', '_', 'r', state_1))
        writeRow(translatedRowsList, (whiteState, '0', '_', 'r', state_0))
        writeRow(translatedRowsList, (whiteState, '_', '_', 'r', state_))
        writeRow(translatedRowsList, (whiteState, '!', '_', 'r', finalState))
        writeRow(translatedRowsList, (state_1, '1', '1', 'r', state_1))
        writeRow(translatedRowsList, (state_1, '0', '1', 'r', state_0))
        writeRow(translatedRowsList, (state_1, '_', '1', 'r', whiteState))
        writeRow(translatedRowsList, (state_1, '!', '1', 'r', finalState))
        writeRow(translatedRowsList, (state_0, '1', '0', 'r', state_1))
        writeRow(translatedRowsList, (state_0, '0', '0', 'r', state_0))
        writeRow(translatedRowsList, (state_0, '_', '0', 'r', whiteState))
        writeRow(translatedRowsList, (state_0, '!', '0', 'r', finalState))
        writeRow(translatedRowsList, (state_, '1', '_', 'r', state_1))
        writeRow(translatedRowsList, (state_, '0', '_', 'r', state_0))
        writeRow(translatedRowsList, (state_, '_', '_', 'r', whiteState))
        writeRow(translatedRowsList, (state_, '!', '_', 'r', finalState))
        writeRow(translatedRowsList, (finalState, '_', '!', 'l', backState))
        writeRow(translatedRowsList, (backState, '#', '*', 'r', state))
        writeRow(translatedRowsList, (backState, '*', '*', 'l', backState))
        writeRow(translatedRowsList, (state, '!', '_', 'r', whiteBackState))
        writeRow(translatedRowsList, (whiteBackState, '*', '!', 'l', state))

  return translatedRowsList

def translator(fileName, rows):
    translatedRowsList = getList()
    writeInFile(fileName.replace('.in', '') + '_semi_infinita.out', translatedRowsList)
    states = []

    for row in rows:
        row = row.replace('\n', '').split()

        if len(row) != 5:
            continue

        if row[0] == '0':
            continue

        if row[0] == '0':
            state = row[0]

        if not (row[0] in states):
            states.append(row[0])

        writeRow(translatedRowsList, row)
      
    translatedRowsList = writeRows(translatedRowsList, states)

    writeInFile(fileName.replace('.in', '') + '_semi_infinita.out', translatedRowsList)
    print('MT duplamente infinita traduzida para semi-infinita com sucesso!\nArquivo gerado com o nome: ' + fileName.replace('.in', '_') + 'semi_infinita.out')

def start():
  fileName = 'sameamount10.in'

  with open(fileName) as file:
      rows = file.readlines()

  aux = 0
  for find in rows:
      if str(aux) in find:
          aux = aux + 1
          lastState = aux
  lastState = lastState - 1

  translator(fileName, rows)

start()