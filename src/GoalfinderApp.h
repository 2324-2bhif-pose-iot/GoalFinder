/*
 * ===============================================================================
* (c) HTL Leonding
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * Licensed under MIT License.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the license.
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * All trademarks used in this document are property of their respective owners.
 * ===============================================================================
 */

#pragma once 
#include <Singleton.h>

class GoalfinderApp : public Singleton<GoalfinderApp> {
	public:
		/** Destructor */
		virtual ~GoalfinderApp();

		/** Initializes the application. */
		void Init();

		/** Processes one single iteration step. */
		void Process();

		void OnSettingsUpdated();

		GoalfinderApp();
	private:
		friend class Singleton<GoalfinderApp> ;
		/** Singleton constructor */
		
};