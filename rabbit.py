for x in range(0, 100):
	solved = False
	for a in '*+-/':
		for b in '*+-/':
			for c in '*+-/':
				for d in '*+-/':
					for lbracket in range(0,5):
						for rbracket in range(lbracket+2, 6):
							eq = '(' * (lbracket == 0)
							for q in range(1,6):
								eq += str(q)
								if q == lbracket:
									eq += '{%s}'%(q-1)
									eq += '('
								elif q == rbracket:
									eq += ')'
									eq += '{%s}'%(q-1)
								else:
									eq += '{%s}'%(q-1)
								

							eq = eq.replace('{4}','')
							z = eq.format(a,b,c,d)
							try:
								if eval(z) == x:
									print("{0}: {1}".format(x, z))

									solved = True
									break
							except ZeroDivisionError:
								continue
						if solved: break	
					if solved: break	
				if solved: break	
			if solved: break	
		if solved: break	
	if not solved: print('=======')
							